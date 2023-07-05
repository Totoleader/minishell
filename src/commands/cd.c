/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:12:36 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/03 11:49:28 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	change_homedir(t_minishell *mini)
{
	char	*homedir;

	homedir = ft_getenv(mini, "HOME");
	if (!homedir)
		return ;
	else
	{
		if (chdir(homedir) == -1)
			printf("cd: no such file or directory: %s\n", homedir);
		else
		{
			ft_setenv(mini, "OLDPWD", mini->cwd);
			getcwd(mini->cwd, PATH_MAX);
			ft_setenv(mini, "PWD", mini->cwd);
		}
	}
}

//OLDPWD
void	cd_(t_commands *cmds, t_minishell *mini)
{
	if (!cmds->args[1])
		change_homedir(mini);
	else
	{
		if (chdir(cmds->args[1]) == -1)
		{
			error_code = 1;
			if (access(cmds->args[1], F_OK))
				printf("cd: not a directory: %s\n", cmds->args[1]);
			else
				printf("cd: no such file or directory: %s\n", cmds->args[1]);
		}
		else
		{
			error_code = 0;
			ft_setenv(mini, "OLDPWD", mini->cwd);
			getcwd(mini->cwd, PATH_MAX);
			ft_setenv(mini, "PWD", mini->cwd);
		}
	}
}
