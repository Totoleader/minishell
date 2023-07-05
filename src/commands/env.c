/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:20:58 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/05 11:52:00 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_(t_minishell *mini)
{
	t_list	*lst;

	if (!mini)
		return ;
	lst = mini->env;
	while (lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}
