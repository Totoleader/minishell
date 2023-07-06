/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:56:00 by macote            #+#    #+#             */
/*   Updated: 2023/07/05 16:13:25 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup2_(int fd, int std)
{
	if (dup2(fd, std) == -1)
	{
		ft_putstr_fd("dup2() failed\n", STDERR_FILENO);  // pas le droit a perror
		// free
		// exit(EXIT_FAILURE);
	}
	close(fd);
}

int	open_(t_commands *cmd, int in_out)
{
	int	fd;
	
	fd = -1;
	if (in_out == IN && (cmd->type_in == REDIR_IN || cmd->type_in == REDIR_IN_DELIM))
		fd = open(cmd->infile, O_RDONLY);
		
	//should read from stdin	
	// else if (in_out == IN && cmd->type_in == REDIR_IN_DELIM)
	// 	fd = open(cmd->infile, O_RDONLY);
	else if (in_out == OUT && cmd->type_out == REDIR_OUT)
		fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (in_out == OUT && cmd->type_out == REDIR_OUT_APPEND)
		fd = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT, 0777);

	if (fd == -1)
	{
		ft_putstr_fd("open() failed", STDERR_FILENO);
		// free_commands(pip);
		// exit(EXIT_SUCCESS);
	}
	return (fd);
}

void reset_std_in_out(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
}

void	here_doc(t_commands *cmd)
{
	char	*hd_buf;
	int		first;
	int		fd;

	first = 1;
	printf("Welcome to heredoc! Delimiter is %s\n", cmd->infile);
	fd = open("temp", O_WRONLY | O_APPEND | O_CREAT, 0777);
	while (first || hd_buf)
	{
		first = 0;
		hd_buf = readline("> ");
		if (!hd_buf || ft_strncmp(hd_buf, cmd->infile, ft_strlen(hd_buf)) == 0)
		{
			free(hd_buf);
			close(fd);
			return ;
		}
		else
		{
			write(fd, hd_buf, ft_strlen(hd_buf));
			write(fd, "\n", 1);
		}
		free(hd_buf);
	}
	close(fd);
}

void redir(t_commands *cmd, int is_not_first, int *pipe_fd, int last_pipe)
{
	// if (cmd->type_in == REDIR_IN_DELIM)
	// {
	// 	here_doc(cmd);
	// 	free(cmd->infile);
	// 	cmd->infile = ft_strdup("temp");
	// 	cmd->infile_fd = open_(cmd, IN);
	// 	dup2_(cmd->infile_fd, STDIN_FILENO);
	// }
	if (cmd->infile) //there is infile
	{
		cmd->infile_fd = open_(cmd, IN);
		dup2_(cmd->infile_fd, STDIN_FILENO);
	}
	else if (is_not_first)
	{
		dup2_(last_pipe, STDIN_FILENO);
	}
	if (cmd->next)
	{
		dup2_(pipe_fd[WRITE], STDOUT_FILENO);
	}
	else if (cmd->outfile)
	{
		cmd->outfile_fd = open_(cmd, OUT);
		dup2_(cmd->outfile_fd, STDOUT_FILENO);
	}
}
