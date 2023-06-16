/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:20:58 by scloutie          #+#    #+#             */
/*   Updated: 2023/06/16 14:38:43 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_(t_minishell *mini)
{
	t_list	*lst;

	lst	= mini->env;
	while (lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}
