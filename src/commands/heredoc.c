/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:53:42 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/14 15:30:30 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_varname(char *arg)
{
	char	*out;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != ' ')
		i++;
	out = malloc(sizeof(char) * (i + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != ' ')
	{
		out[i] = arg[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

static void	print_env(t_minishell *mini, char *buf, int fd, int *i)
{
	char	*varname;
	char	*varvalue;

	varname = get_varname(&buf[*i + 1]);
	if (!varname)
		return ;
	varvalue = ft_getenv(mini, varname);
	if (varvalue)
		ft_putstr_fd(varvalue, fd);
	(*i) += ft_strlen(varname);
	free(varname);
}

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

void	here_doc(t_commands *cmd, t_minishell *mini)
{
	char	*hd_buf;
	int		first;
	int		fd;

	first = 1;
	fd = open(TEMP_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		return ;
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
			close(fd);
			return ;
		}
		else
			convert_write(hd_buf, fd, mini);
		write(fd, "\n", 1);
		free(hd_buf);
	}
	close(fd);
}
