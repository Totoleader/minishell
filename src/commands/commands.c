/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:30:29 by macote            #+#    #+#             */
/*   Updated: 2023/06/19 10:59:03 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_command(t_input command, t_minishell *mini)
{
	if (!ft_strncmp(command.command, "", 1))
		return ;
	else if (!ft_strncmp(command.command, "exit", 5))
		exit_();
	else if (!ft_strncmp(command.command, "echo", 5))
		echo_(command);
	else if (!ft_strncmp(command.command, "env", 3))
		env_(mini);
	else if (!ft_strncmp(command.command, "export", 6))
		export_(mini, command);
	else if (!ft_strncmp(command.command, "unset", 5))
		unset_(mini, command);
	else if (!ft_strncmp(command.command, "pwd", 3))
		pwd_(mini);
	else
		printf("minishell: %s: command not found\n", command.command);
}
