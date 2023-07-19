/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:04:35 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/19 12:07:37 by scloutie         ###   ########.fr       */
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
	out = ft_calloc(i + 1, sizeof(char));
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

void	print_env(t_minishell *mini, char *buf, int fd, int *i)
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

void	exit_hd(t_commands *cmd, t_minishell *mini, int fd)
{
	free_cmds(cmd);
	close(mini->std_bak[IN]);
	close(mini->std_bak[OUT]);
	close(fd);
	free_mini(mini);
}
