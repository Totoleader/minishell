/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:56:00 by macote            #+#    #+#             */
/*   Updated: 2023/07/07 13:22:46 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup2_(int fd, int std)
{
	if (dup2(fd, std) == -1)
		ft_putstr_fd("dup2() failed\n", STDERR_FILENO);
	close(fd);
}

int	open_(t_commands *cmd, int in_out)
{
	int	fd;
	
	fd = -1;
	if (in_out == IN && (cmd->type_in == REDIR_IN || cmd->type_in == REDIR_IN_DELIM))
		fd = open(cmd->infile, O_RDONLY);
	else if (in_out == OUT && cmd->type_out == REDIR_OUT)
		fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (in_out == OUT && cmd->type_out == REDIR_OUT_APPEND)
		fd = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT, 0777);

	if (fd == -1)
		ft_putstr_fd("open() failed", STDERR_FILENO);
	return (fd);
}

void reset_std_in_out(int *std_backup)
{
	dup2(std_backup[IN], STDIN_FILENO);
	dup2(std_backup[OUT], STDOUT_FILENO);
}

void redir(t_minishell *mini, t_commands *cmd, int is_not_first, int *pipe_fd, int last_pipe)
{
	if (cmd->type_in == REDIR_IN_DELIM)
	{
		here_doc(cmd, mini);
		free(cmd->infile);
		cmd->infile = ft_strdup("temp");
		cmd->infile_fd = open_(cmd, IN);
		dup2_(cmd->infile_fd, STDIN_FILENO);
	}
	else if (cmd->infile)
	{
		cmd->infile_fd = open_(cmd, IN);
		dup2_(cmd->infile_fd, STDIN_FILENO);
	}
	else if (is_not_first)
	{
		dup2_(last_pipe, STDIN_FILENO);
	}
	if (cmd->outfile)
	{
		cmd->outfile_fd = open_(cmd, OUT);
		dup2_(cmd->outfile_fd, STDOUT_FILENO);
	}
	else if (cmd->next)
	{
		dup2_(pipe_fd[WRITE], STDOUT_FILENO);
	}
}
