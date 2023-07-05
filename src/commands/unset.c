/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:21:06 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/05 11:52:20 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Finds the env variable at specified index and deletes it
 * If it is the first in the list, adjusts the first pointer
 **/
static void	env_delete(t_minishell *mini, int index)
{
	int		i;
	t_list	*temp;
	t_list	*lst;

	i = 0;
	lst = mini->env;
	if (index == 0)
	{
		temp = mini->env->next;
		ft_lstdelone(mini->env, free);
		mini->env = temp;
	}
	else
	{
		while (i != index)
		{
			temp = lst;
			lst = lst->next;
			i++;
		}
		temp->next = lst->next;
		ft_lstdelone(lst, free);
	}
}

// TODO peut etre afficher message d'erreur si identifier est pas valide
void	unset_(t_minishell *mini, t_commands *command)
{
	t_list	*lst;
	int		size;
	int		i;
	char	*to_find;

	lst = mini->env;
	size = ft_lstsize(lst);
	i = -1;
	if (command->args[1] == NULL)
		return ;
	to_find = ft_strjoin(command->args[1], "=");
	while (lst && ++i < size)
	{
		if (!ft_strncmp(lst->content, to_find, ft_strlen(to_find)))
			break ;
		lst = lst->next;
	}
	free(to_find);
	if (!lst)
		return ;
	else
		env_delete(mini, i);
}
