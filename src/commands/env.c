/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:20:58 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/03 11:50:27 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_(t_minishell *mini)
{
	t_list	*lst;

	error_code = 0;
	if (!mini)
		return ;
	lst = mini->env;
	while (lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}
