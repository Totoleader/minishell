/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:30:29 by macote            #+#    #+#             */
/*   Updated: 2023/07/05 15:37:59 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void redir(t_commands *cmds, int *pipe_fd, int previous_pipe, int is_not_first)
// {
// 	//** noter quand c'est "">>" et "<<" **
// 	close(pipe_fd[READ]);
// 	//in
// 	if (cmds->infile) //there is infile
// 	{
// 		cmds->infile_fd = open(cmds->infile, O_RDONLY);//close?
// 		dup2(cmds->infile_fd, STDIN_FILENO);
// 		close(cmds->infile_fd);
// 	}
// 	else if (is_not_first) //if not first and no infile, read in pipe
// 	{
// 		dup2(previous_pipe, STDIN_FILENO);
// 		close(previous_pipe);
// 	}
// 	// //out
// 	if (cmds->next) //is not last
// 	{
// 		dup2(pipe_fd[WRITE], STDOUT_FILENO);
// 		close(pipe_fd[WRITE]);
// 	}
// 	else if (cmds->outfile) //there is no pipe but there is outfile
// 	{
// 		cmds->outfile_fd = open(cmds->outfile, O_WRONLY | O_CREAT, 0644);
// 		dup2(cmds->outfile_fd, STDOUT_FILENO);
// 		close(cmds->outfile_fd);
// 	}
// }

// void exec_cmd_master(t_commands *cmds, t_minishell *mini)
// {
// 	t_commands	*current;
// 	int			pipe_fd[2];
// 	int			pid;
// 	int			previous_pipe;
// 	int			is_not_first;

// 	is_not_first = 0;
// 	previous_pipe = -1;
// 	current = cmds;
// 	while (current)
// 	{
// 		//create pipe if needed, fork no matter what
// 		if (is_not_first)
// 			previous_pipe = pipe_fd[READ];
// 		if (current->next)
// 			pipe(pipe_fd);
// 		pid = fork();
// 		//execute command in child
// 		if (pid == 0)
// 		{
// 			redir(current, pipe_fd, previous_pipe, is_not_first);
// 			execute_command(current, mini);
// 			exit(0);
// 		}
// 		waitpid(0, NULL, 0);
// 		// close(previous_pipe);

// 		//is first
// 		if (!is_not_first)
// 			close(pipe_fd[WRITE]);
// 		else if (is_not_first && current->next)
// 		{
// 			close(pipe_fd[WRITE]);
// 			close(previous_pipe);
// 		}
// 		else
// 			close(pipe_fd[READ]);
		

// 		current = current->next;
// 		is_not_first++;
// 	}
// }

// void execve_command(t_commands *cmds)
// {
// 	// char *argv[] = { "/usr/bin/sort", NULL};
// 	// mini = NULL;
// 	// cmds = NULL;
// 	//if command not found dont do.....
// 	if (execve(cmds->args[0], cmds->args, NULL) == -1)
// 	{
// 		// printf("minishell: %s: command not found\n", cmds->args[0]);
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	execute_command(t_commands *cmds, t_minishell *mini)
// {
// 	if (!cmds->args)
// 		return ;
// 	else if (!ft_strncmp(cmds->args[0], "exit", 5))
// 		exit_();
// 	else if (!ft_strncmp(cmds->args[0], "echo", 5))
// 		echo_(&cmds->args[1]);
// 	else if (!ft_strncmp(cmds->args[0], "env", 3))
// 		env_(mini);
// 	else if (!ft_strncmp(cmds->args[0], "export", 6))
// 		export_(mini, cmds);
// 	else if (!ft_strncmp(cmds->args[0], "unset", 5))
// 		unset_(mini, cmds);
// 	else if (!ft_strncmp(cmds->args[0], "pwd", 3))
// 		pwd_(mini);
// 	else if (!ft_strncmp(cmds->args[0], "cd", 2))
// 		cd_(cmds, mini);
// 	else
// 	{
// 		get_path(cmds, mini);
// 		execve_command(cmds);
// 		// 	printf("found: %s\n", cmds->args[0]);
// 		// else
// 		// 	printf("command not found\n");
// 	}

// 		// printf("minishell: %s: command not found\n", cmds->args[0]);
// }

void cmd_not_found(char *str)
{
	int pid;
	
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": Command not found.\n", STDERR_FILENO);

	// free
	pid = fork();
	if (pid == 0)
		exit(127);// a verifier <--------------------------------------------------------
}

// int check_access_builtin(t_commands *cmds)
// {
// 	int pid;
	
// 	if (cmds->infile && access(cmds->infile, R_OK) == -1)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 			exit(EXIT_FAILURE);	
// 		return (FALSE);
// 	}
// 	else if (cmds->outfile && access(cmds->infile, W_OK) == -1)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 			exit(EXIT_FAILURE);	
// 		return (FALSE);
// 	}
// 	return (TRUE);
// }

int	execute_builtin(t_commands *cmds, t_minishell *mini)
{
	if (!cmds->args)//////////////////////////////////////////////////////////////////////////////
		return (TRUE);
	if (!ft_strncmp(cmds->args[0], "exit", 5))
		return (exit_(), TRUE);
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

void *execve_command(t_commands *cmds, t_minishell *mini)
{
	// char *argv[] = { "/usr/bin/sort", NULL};
	// mini = NULL;
	// cmds = NULL;
	//if command not found dont do.....
	int pid;

	if (!get_path(cmds, mini))
		return (cmd_not_found(cmds->args[0]), NULL);

	pid = fork();
	if (pid == 0)
	{
		// close(pipe_fd[0]);
		// check_access(cmds);////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// printf("minishell: %s: command not found\n", cmds->args[0]);
		execve(cmds->args[0], cmds->args, NULL);
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

void exec_cmd_master(t_commands *cmds, t_minishell *mini)
{
	t_commands *current;
	int stdin_backup;
	int stdout_backup;
	int is_not_first;
	int pipe_fd[2];
	int last_pipe;

	current = cmds;
	is_not_first = 0;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	//rediriger

	//executer la commande / fork juste quand c'est pas un builtin
	while (current)
	{
		//check acess before and dont exec cmd
		if (current->infile && access(current->infile, F_OK | R_OK) != 0)
		{
			error_code = 1;
			printf("minishell: %s: Permission denied\n", current->infile);
			current = current->next;
			continue ;
		}
		else if (current->outfile && access(current->outfile, F_OK) == 0 && access(current->outfile, W_OK) != 0)
		{
			error_code = 1;
			printf("minishell: %s: Permission denied\n", current->outfile);
			current = current->next;
			continue ;
		}

		if (current->next)
			pipe(pipe_fd);
		redir(current, is_not_first, pipe_fd, last_pipe);
		if (!execute_builtin(current, mini))
			execve_command(current,mini);
		if (current->next)
			last_pipe = pipe_fd[READ];

		is_not_first++;
		current = current->next;
		reset_std_in_out(stdin_backup, stdout_backup);
	}
}
