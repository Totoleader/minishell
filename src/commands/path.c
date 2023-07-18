/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:26:50 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/18 16:49:27 by scloutie         ###   ########.fr       */
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

int	ft_free_tab(char **tabl)
{
	int	i;

	i = 0;
	if (!tabl)
		return (1);
	while (tabl[i])
	{
		free(tabl[i]);
		i++;
	}
	free(tabl);
	return (1);
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
	if ((!ft_strncmp(cmd->args[0], "./", 2) || ft_strchr(cmd->args[0], '/'))
		&& access(cmd->args[0], F_OK) == 0)
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
			return (ft_free_tab(tabenv));
		free(cmd->args[0]);
	}
	ft_free_tab(tabenv);
	cmd->args[0] = ft_strdup(cmd_name);
	return (0);
}
