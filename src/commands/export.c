/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:43:48 by scloutie          #+#    #+#             */
/*   Updated: 2023/06/16 16:50:50 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_(t_minishell *mini, t_input command)
{
	//TODO verifier si format est valide
	if (command.args[0] == NULL)
		env_(mini);
	else
		ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(command.args[0])));
}
