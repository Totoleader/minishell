/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:30:29 by macote            #+#    #+#             */
/*   Updated: 2023/06/20 14:27:30 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_command(t_commands *cmds, t_minishell *mini)
{
	if (!cmds->args)
		return ;
	else if (!ft_strncmp(cmds->args[0], "exit", 5))
		exit_();
	// else if (!ft_strncmp(command.command, "echo", 5))
	// 	echo_(command);
	else if (!ft_strncmp(cmds->args[0], "env", 3))
		env_(mini);
	// else if (!ft_strncmp(command.command, "export", 6))
	// 	export_(mini, command);
	// else if (!ft_strncmp(command.command, "unset", 5))
	// 	unset_(mini, command);
	else if (!ft_strncmp(cmds->args[0], "pwd", 3))
		pwd_(mini);
	else if (!ft_strncmp(cmds->args[0], "cd", 3))
		cd_(cmds, mini);
	else
		printf("minishell: %s: command not found\n", cmds->args[0]);
}
