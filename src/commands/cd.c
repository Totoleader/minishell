/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:12:36 by scloutie          #+#    #+#             */
/*   Updated: 2023/06/20 15:57:59 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_env_cwd(t_minishell *mini, t_list *pwd_node)
{
	char	*full_var;

	if (pwd_node->content)
		free(pwd_node->content);
	full_var = ft_strjoin("PWD=", mini->cwd);
	if (!full_var)
		return ;
	pwd_node->content = full_var;
}

void	cd_(t_commands *cmds, t_minishell *mini)
{
	t_list	*pwd_node;

	if (!cmds->args[1])
		return ;
	else
	{
		if (chdir(cmds->args[1]) == -1)
		{
			if (access(cmds->args[1], X_OK))
				printf("cd: not a directory: %s\n", cmds->args[1]);
			else
				printf("cd: no such file or directory: %s\n", cmds->args[1]);
		}
		else
		{
			getcwd(mini->cwd, PATH_MAX);
			pwd_node = ft_getenv_node(mini, "PWD");
			if (pwd_node)
				replace_env_cwd(mini, pwd_node);
		}
	}
}
