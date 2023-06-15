/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:30:29 by macote            #+#    #+#             */
/*   Updated: 2023/06/15 14:11:59 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_command(t_input command)
{
	if (command.quoted[0] && command.args[0] && *(command.args[0] - 2) != ' ' && *(command.args[0]
			- 2) != '\0')
	{
		printf("error command not found\n");
		return;
	}
	if (!ft_strncmp(command.command, "", 1))
		return ;
	else if (!ft_strncmp(command.command, "exit", 5))
		exit_();
	else if (!ft_strncmp(command.command, "echo", 5))
		echo_(command);
	else
		printf("minishell: %s: command not found", command.command);
}