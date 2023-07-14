/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:30:29 by macote            #+#    #+#             */
/*   Updated: 2023/07/14 11:46:04 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void cmd_not_found(char *str)
{
	error_code = 127;
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": Command not found.\n", STDERR_FILENO);
}

int	execute_builtin(t_commands *cmds, t_minishell *mini)
{
	if (!cmds->args)//////////////////////////////////////////////////////////////////////////////
		return (TRUE);
	if (!ft_strncmp(cmds->args[0], "exit", 5))
		return (exit_(cmds, mini), TRUE);
	else if (!ft_strncmp(cmds->args[0], "echo", 5))
		return (echo_(&cmds->args[1]), TRUE);
	else if (!ft_strncmp(cmds->args[0], "env", 3))
		return (env_(mini), TRUE);
	else if (!ft_strncmp(cmds->args[0], "export", 6))
		return (export_(mini, cmds), TRUE);
	else if (!ft_strncmp(cmds->args[0], "unset", 5))
		return (unset_(mini, cmds), TRUE);
	else if (!ft_strncmp(cmds->args[0], "pwd", 3))
		return (pwd_(mini), TRUE);
	else if (!ft_strncmp(cmds->args[0], "cd", 2))
		return (cd_(cmds, mini), TRUE);
	return (FALSE);
}

//helper to execve_command()
void check_access(t_commands *cmds)
{
	if (cmds->infile && access(cmds->infile, R_OK) == -1)
		exit(EXIT_FAILURE);
	if (cmds->outfile && access(cmds->infile, W_OK) == -1)
		exit (EXIT_FAILURE);
}

char	**convert_env(t_minishell *mini)
{
	t_list	*current;
	char	**envtab;
	int		i;

	current = mini->env;
	i = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	envtab = malloc(sizeof(char *) * (i + 1));
	current = mini->env;
	i = -1;
	while (current != NULL)
	{
		envtab[++i] = ft_strdup(current->content);
		current = current->next;
	}
	envtab[++i] = NULL;
	return (envtab);
}

void *execve_command(t_commands *cmds, t_minishell *mini, int *std_backup, int *pipe_fd)
{
	int pid;
	char **env_;
	
	if (!get_path(cmds, mini))
		return (cmd_not_found(cmds->args[0]), NULL);
	pid = fork();
	if (pid == 0)
	{
		if (cmds->next)
			close(pipe_fd[READ]);
		// else if (is_not_first && !cmds->next)
		// 	close(pipe_fd[WRITE]);
		env_ = convert_env(mini);
		// std_backup = NULL;
		close(std_backup[OUT]);
		close(std_backup[IN]);
		execve(cmds->args[0], cmds->args, env_);
		exit(EXIT_FAILURE);
	}
	waitpid(0, &error_code, 0);
	error_code = WEXITSTATUS(error_code);
	return (NULL);
}

void exit_success()
{
	int pid;
	
	pid = fork();
	if (pid == 0)
		exit(EXIT_SUCCESS);
}

int check_file(t_commands **cmd)
{
	//check acess before and dont exec cmd
	if ((*cmd)->type_in != REDIR_IN_DELIM && (*cmd)->infile && access((*cmd)->infile, F_OK | R_OK) != 0)
	{
		error_code = 1;
		printf("minishell: %s: Permission denied\n", (*cmd)->infile);
		(*cmd) = (*cmd)->next;
		return(TRUE);
	}
	else if ((*cmd)->outfile && access((*cmd)->outfile, F_OK) == 0 && access((*cmd)->outfile, W_OK) != 0)
	{
		error_code = 1;
		printf("minishell: %s: Permission denied\n", (*cmd)->outfile);
		(*cmd) = (*cmd)->next;
		return(TRUE);
	}
	return (FALSE);
}

void exec_cmd_master(t_commands *cmds, t_minishell *mini)
{
	t_commands *current;
	int is_not_first;
	int std_backup[2];
	int pipe_fd[2];
	int last_pipe;

	current = cmds;
	is_not_first = 0;
	std_backup[IN] = dup(STDIN_FILENO);
	std_backup[OUT] = dup(STDOUT_FILENO);
	while (current)
	{
		if (check_file(&current))
			continue ;
		if (current->next)
			pipe(pipe_fd);
		redir(mini, current, is_not_first, pipe_fd, last_pipe);
		if (!execute_builtin(current, mini))
			execve_command(current, mini, std_backup, pipe_fd);
		if (current->next)
			last_pipe = pipe_fd[READ];
		if (current->type_in == REDIR_IN_DELIM)
			unlink(TEMP_FILE);
		is_not_first++;
		current = current->next;
		reset_std_in_out(std_backup);
	}
	close(std_backup[IN]);
	close(std_backup[OUT]);
}
