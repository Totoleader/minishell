/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:53:42 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/18 11:34:09 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_specialcase(t_minishell *mini, char *buf, int fd, int *i)
{
	char	*errval_text;

	if (buf[*i + 1] == ' ' || buf[*i + 1] == '$' || buf[*i + 1] == '\0')
		write(fd, "$", 1);
	else if (buf[*i + 1] == '?')
	{
		errval_text = ft_itoa(g_error_code);
		if (errval_text)
		{
			write(fd, errval_text, ft_strlen(errval_text));
			(*i)++;
			free(errval_text);
		}
	}
	else if (ft_isalpha(buf[*i + 1]) || buf[*i + 1] == '_')
		print_env(mini, buf, fd, i);
	else
		write(fd, &buf[*i], 1);
}

static void	convert_write(char *buf, int fd, t_minishell *mini)
{
	int	i;

	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '$')
			print_specialcase(mini, buf, fd, &i);
		else
			write(fd, &buf[i], 1);
	}
}

void	here_doc(t_commands *cmd, t_minishell *mini, int fd)
{
	char	*hd_buf;
	int		first;

	first = 1;
	while (first || hd_buf)
	{
		first = 0;
		hd_buf = readline("> ");
		if (ft_strchr(hd_buf, 0) == hd_buf)
			;
		else if (hd_buf == NULL || ft_strncmp(hd_buf, cmd->infile,
				ft_strlen(hd_buf)) == 0)
		{
			free(hd_buf);
			exit_hd(cmd, mini, fd);
			exit(0);
		}
		else
			convert_write(hd_buf, fd, mini);
		write(fd, "\n", 1);
		free(hd_buf);
	}
	free(hd_buf);
	exit_hd(cmd, mini, fd);
	exit(1);
}

int	exec_heredoc(t_commands *cmd, t_minishell *mini)
{
	int		pid;
	pid_t	wstatus;

	init_sighandler(HEREDOC);
	mini->hd_fd = open(TEMP_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (mini->hd_fd < 0)
		return (1);
	mini->cmds = cmd;
	pid = fork();
	if (pid == 0)
		here_doc(cmd, mini, mini->hd_fd);
	init_sighandler(IGNORE);
	waitpid(0, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		if (WEXITSTATUS(wstatus) == 1)
		{
			close(mini->hd_fd);
			unlink(TEMP_FILE);
			return (1);
		}
	}
	close(mini->hd_fd);
	return (0);
}
