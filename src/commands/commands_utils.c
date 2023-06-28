/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:56:00 by macote            #+#    #+#             */
/*   Updated: 2023/06/28 15:03:29 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup2_(int fd, int std)
{
	if (dup2(fd, std) == -1)
	{
		ft_putstr_fd("dup2() failed", STDERR_FILENO);  // pas le droit a perror
		// free
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int	open_(t_commands *cmd, int in_out)
{
	int	fd;
	
	fd = -1;
	if (in_out == IN && cmd->type_in == REDIR_IN)
		fd = open(cmd->infile, O_RDONLY);
		
	//should read from stdin	
	// else if (in_out == IN && cmd->type_in == REDIR_IN_DELIM)
	// 	fd = open(cmd->infile, O_RDONLY);
	else if (in_out == OUT && cmd->type_out == REDIR_OUT)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT, 0644);
	else if (in_out == OUT && cmd->type_out == REDIR_OUT_APPEND)
		fd = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);

	if (fd == -1)
	{
		ft_putstr_fd("open() failed", STDERR_FILENO);
		// free_commands(pip);
		exit(EXIT_SUCCESS);
	}
	return (fd);
}

void reset_std_in_out(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
}

void redir(t_commands *cmd, int is_not_first, int *pipe_fd)
{
	if (cmd->infile) //there is infile
	{
		cmd->infile_fd = open_(cmd, IN);
		dup2_(cmd->infile_fd, STDIN_FILENO);
	}
	else if (is_not_first)
	{
		dup2_(pipe_fd[READ], STDIN_FILENO);
	}
	if (cmd->outfile)
	{
		cmd->outfile_fd = open_(cmd, OUT);
		dup2_(cmd->outfile_fd, STDOUT_FILENO);
	}
	else if (cmd->next)
	{
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
	}
}
