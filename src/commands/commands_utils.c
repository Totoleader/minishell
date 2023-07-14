/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:56:00 by macote            #+#    #+#             */
/*   Updated: 2023/07/14 15:26:42 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//boosted dup2 funtion 
void	dup2_(int fd, int std)
{
	if (dup2(fd, std) == -1)
		ft_putstr_fd("dup2() failed\n", STDERR_FILENO);
	close(fd);
}

//opens a file the right way
int	open_(t_commands *cmd, int in_out)
{
	int	fd;

	fd = -1;
	if (in_out == IN && (cmd->type_in == REDIR_IN
			|| cmd->type_in == REDIR_IN_DELIM))
		fd = open(cmd->infile, O_RDONLY);
	else if (in_out == OUT && cmd->type_out == REDIR_OUT)
		fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (in_out == OUT && cmd->type_out == REDIR_OUT_APPEND)
		fd = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd == -1)
		ft_putstr_fd("open() failed", STDERR_FILENO);
	return (fd);
}

//resets the stdin and stdout after having done redirections
void	reset_std_in_out(int *std_backup)
{
	dup2(std_backup[IN], STDIN_FILENO);
	dup2(std_backup[OUT], STDOUT_FILENO);
}

//does the right output redirections
void	redir_in(t_minishell *mini, t_commands *cmd, int is_not_first,
		int last_pipe)
{
	if (cmd->type_in == REDIR_IN_DELIM)
	{
		here_doc(cmd, mini);
		free(cmd->infile);
		cmd->infile = ft_strdup(TEMP_FILE);
		cmd->infile_fd = open_(cmd, IN);
		dup2_(cmd->infile_fd, STDIN_FILENO);
		if (is_not_first)
			close(last_pipe);
	}
	else if (cmd->infile)
	{
		cmd->infile_fd = open_(cmd, IN);
		dup2_(cmd->infile_fd, STDIN_FILENO);
		if (is_not_first)
			close(last_pipe);
	}
	else if (is_not_first)
		dup2_(last_pipe, STDIN_FILENO);
}

//does the right input redirections
void	redir_out(t_commands *cmd, int *pipe_fd)
{
	if (cmd->outfile)
	{
		cmd->outfile_fd = open_(cmd, OUT);
		dup2_(cmd->outfile_fd, STDOUT_FILENO);
		if (cmd->next)
			close(pipe_fd[WRITE]);
	}
	else if (cmd->next)
		dup2_(pipe_fd[WRITE], STDOUT_FILENO);
}
