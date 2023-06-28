/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:12:36 by scloutie          #+#    #+#             */
/*   Updated: 2023/06/28 13:48:27 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	replace_env_cwd(t_minishell *mini, t_list *pwd_node)
{
	char	*full_var;

	if (pwd_node->content)
		free(pwd_node->content);
	full_var = ft_strjoin("PWD=", mini->cwd);
	if (!full_var)
		return ;
	pwd_node->content = full_var;
}

static void	change_homedir(t_minishell *mini)
{
	char	*homedir;
	t_list	*pwd_node;

	homedir = ft_getenv(mini, "HOME");
	if (!homedir)
		return ;
	else
	{
		if (chdir(homedir) == -1)
			printf("cd: no such file or directory: %s\n", homedir);
		else
		{
			getcwd(mini->cwd, PATH_MAX);
			pwd_node = ft_getenv_node(mini, "PWD");
			if (pwd_node)
				replace_env_cwd(mini, pwd_node);
		}
	}
}

// TODO: cd without arguments changes to HOME directory
void	cd_(t_commands *cmds, t_minishell *mini)
{
	t_list	*pwd_node;

	if (!cmds->args[1])
		change_homedir(mini);
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
