/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:30:29 by macote            #+#    #+#             */
/*   Updated: 2023/06/27 13:07:06 by scloutie         ###   ########.fr       */
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

void	ft_free_tab(char **tabl)
{
	int	i;

	i = 0;
	if (!tabl)
		return ;
	while (tabl[i])
	{
		free(tabl[i]);
		i++;
	}
	free(tabl);
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
	if (access(cmd->args[0], F_OK) == 0)
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
		{
			ft_free_tab(tabenv);
			return (1);
		}
		free(cmd->args[0]);
	}
	ft_free_tab(tabenv);
	return (0);
}

void	execute_command(t_commands *cmds, t_minishell *mini)
{
	if (!cmds->args)
		return ;
	else if (!ft_strncmp(cmds->args[0], "exit", 5))
		exit_();
	else if (!ft_strncmp(cmds->args[0], "echo", 5))
		echo_(cmds);
	else if (!ft_strncmp(cmds->args[0], "env", 3))
		env_(mini);
	else if (!ft_strncmp(cmds->args[0], "export", 6))
		export_(mini, cmds);
	else if (!ft_strncmp(cmds->args[0], "unset", 5))
		unset_(mini, cmds);
	else if (!ft_strncmp(cmds->args[0], "pwd", 3))
		pwd_(mini);
	else if (!ft_strncmp(cmds->args[0], "cd", 2))
		cd_(cmds, mini);
	else
	{
		if (get_path(cmds, mini))
			printf("found: %s\n", cmds->args[0]);
		else
			printf("command not found\n");
	}
}
