/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:43:48 by scloutie          #+#    #+#             */
/*   Updated: 2023/06/27 13:48:00 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_(t_minishell *mini, t_commands *command)
{
	char	*envar;

	if (command->args[1] == NULL)
		env_(mini);
	else
	{
		if (!ft_strchr(command->args[1], '='))
			return ;
		else
		{
			envar = ft_strdup(command->args[1]);
			if (!envar)
				return ;
			ft_lstadd_back(&mini->env, ft_lstnew(envar));
		}
	}
}
