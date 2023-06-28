/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:30:29 by macote                                   */
/*   Updated: 2023/06/28 10:32:16 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_env(t_minishell *mini)
{
	char	*env;
	char	**tabenv;

	env = ft_getenv(mini, "PATH");
	if (!env)
		return (NULL);
	tabenv = ft_split(env, ':');
	return (tabenv);
}

void	ft_free_tab(char **tabl)
{
	int	i;

	i = 0;
	if (!tabl)
		return ;
	while (tabl[i])
	{
		free(tabl[i]);
		i++;
	}
	free(tabl);
}

char	*join_path(char *dir, char *cmd_name)
{
	char	*path;
	char	*temp;

	temp = ft_strjoin(dir, "/");
	path = ft_strjoin(temp, cmd_name);
	free(temp);
	return (path);
}

int	get_path(t_commands *cmd, t_minishell *mini)
{
	char	**tabenv;
	int		i;
	char	cmd_name[PATH_MAX];

	i = -1;
	if (access(cmd->args[0], F_OK) == 0)
		return (1);
	tabenv = split_env(mini);
	ft_strlcpy(cmd_name, cmd->args[0], PATH_MAX);
	free(cmd->args[0]);
	if (!tabenv)
		return (0);
	while (tabenv[++i] != NULL)
	{
		cmd->args[0] = join_path(tabenv[i], cmd_name);
		if (access(cmd->args[0], F_OK) == 0)
		{
			ft_free_tab(tabenv);
			return (1);
		}
		free(cmd->args[0]);
	}
	ft_free_tab(tabenv);
	return (0);
}

void redir(t_commands *cmds, int *pipe_fd, int previous_pipe, int is_not_first)
{
	//** noter quand c'est "">>" et "<<" **
	close(pipe_fd[READ]);
	//in
	if (cmds->infile) //there is infile
	{
		cmds->infile_fd = open(cmds->infile, O_RDONLY);//close?
		dup2(cmds->infile_fd, STDIN_FILENO);
		close(cmds->infile_fd);
	}
	else if (is_not_first) //if not first and no infile, read in pipe
	{
		dup2(previous_pipe, STDIN_FILENO);
		close(previous_pipe);
	}
	// //out
	if (cmds->next) //is not last
	{
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
	}
	else if (cmds->outfile) //there is no pipe but there is outfile
	{
		cmds->outfile_fd = open(cmds->outfile, O_WRONLY | O_CREAT, 0644);
		dup2(cmds->outfile_fd, STDOUT_FILENO);
		close(cmds->outfile_fd);
	}
}

void exec_cmd_master(t_commands *cmds, t_minishell *mini)
{
	t_commands	*current;
	int			pipe_fd[2];
	int			pid;
	int			previous_pipe;
	int			is_not_first;

	is_not_first = 0;
	previous_pipe = -1;
	current = cmds;
	while (current)
	{
		//create pipe if needed, fork no matter what
		if (is_not_first)
			previous_pipe = pipe_fd[READ];
		if (current->next)
			pipe(pipe_fd);
		pid = fork();
		//execute command in child
		if (pid == 0)
		{
			redir(current, pipe_fd, previous_pipe, is_not_first);
			execute_command(current, mini);
			exit(0);
		}
		waitpid(0, NULL, 0);
		// close(previous_pipe);

		//is first
		if (!is_not_first)
			close(pipe_fd[WRITE]);
		else if (is_not_first && current->next)
		{
			close(pipe_fd[WRITE]);
			close(previous_pipe);
		}
		else
			close(pipe_fd[READ]);
		

		current = current->next;
		is_not_first++;
	}
}

void execve_command(t_commands *cmds, t_minishell *mini)
{
	char *argv[] = { "/usr/bin/sort", NULL};
	mini = NULL;
	cmds = NULL;
	//if command not found dont do.....
	if (execve("/usr/bin/sort", argv, NULL) == -1)
	{
		// printf("minishell: %s: command not found\n", cmds->args[0]);
		exit(EXIT_FAILURE);
	}
}

void	execute_command(t_commands *cmds, t_minishell *mini)
{
	if (!cmds->args)
		return ;
	else if (!ft_strncmp(cmds->args[0], "exit", 5))
		exit_();
	else if (!ft_strncmp(cmds->args[0], "echo", 5))
		echo_(&cmds->args[1]);
	else if (!ft_strncmp(cmds->args[0], "env", 3))
		env_(mini);
	else if (!ft_strncmp(cmds->args[0], "export", 6))
		export_(mini, cmds);
	else if (!ft_strncmp(cmds->args[0], "unset", 5))
		unset_(mini, cmds);
	else if (!ft_strncmp(cmds->args[0], "pwd", 3))
		pwd_(mini);
	else if (!ft_strncmp(cmds->args[0], "cd", 2))
		cd_(cmds, mini);
	else
	{
		if (get_path(cmds, mini))
			printf("found: %s\n", cmds->args[0]);
		else
			printf("command not found\n");
	}
	execve_command(cmds, mini);

		// printf("minishell: %s: command not found\n", cmds->args[0]);
}
