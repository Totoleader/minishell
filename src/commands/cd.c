/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:12:36 by scloutie          #+#    #+#             */
/*   Updated: 2023/06/20 14:58:50 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_(t_commands *cmds, t_minishell *mini)
{
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
			getcwd(mini->cwd, PATH_MAX);
	}
}
