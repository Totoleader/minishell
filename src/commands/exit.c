/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:23:07 by macote            #+#    #+#             */
/*   Updated: 2023/07/19 11:59:36 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//exit builtin
void	exit_(t_commands *cmds, t_minishell *mini)
{
	long long	return_value;

	if (cmds->args[1])
	{
		return_value = ft_atoi(cmds->args[1]);
		if (return_value > INT_MAX || return_value < INT_MIN)
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			printf("Minishell: exit: %s: numeric argument required",
				cmds->args[1]);
			return_value = 255;
		}
	}
	else
		return_value = 0;
	close(mini->std_bak[IN]);
	close(mini->std_bak[OUT]);
	free_all(cmds, mini);
	exit(return_value);
}
