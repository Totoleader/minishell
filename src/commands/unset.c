/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:21:06 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/06 13:31:18 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valididentifier(char *arg)
{
	int		is_valid_first;
	int		is_valid_string;
	int		i;

	if (!arg)
		return (0);
	is_valid_first = (arg[0] == '_' || ft_isalpha(arg[0]));
	if (!is_valid_first)
		return (0);
	is_valid_string = 1;
	i = 0;
	while (arg[i])
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i]))
			is_valid_string = 0;
		i++;
	}
	return (is_valid_string && is_valid_first);
}

/**
 * Finds the env variable at specified index and deletes it
 * If it is the first in the list, adjusts the first pointer
 **/
static void	env_delete(t_minishell *mini, char *var)
{
	t_list	*temp;
	t_list	*lst;

	lst = mini->env;
	temp = lst;
	if (!ft_strncmp(mini->env->content, var, ft_strlen(var)))
	{
		temp = mini->env->next;
		ft_lstdelone(mini->env, free);
		mini->env = temp;
	}
	else
	{
		while (lst != NULL)
		{
			if (!ft_strncmp(lst->content, var, ft_strlen(var)))
			{
				temp->next = lst->next;
				ft_lstdelone(lst, free);
				break ;
			}
			temp = lst;
			lst = lst->next;
		}
	}
}

// TODO peut etre afficher message d'erreur si identifier est pas valide
void	unset_(t_minishell *mini, t_commands *command)
{
	t_list	*lst;
	int		i;
	char	*to_find;

	error_code = 0;
	lst = mini->env;
	i = 1;
	while (command->args[i] != NULL)
	{
		to_find = ft_strjoin(command->args[i], "=");
		if (!to_find)
		{
			i++;
			continue ;
		}
		else if (is_valididentifier(command->args[i]))
			env_delete(mini, to_find);
		else
			ft_putstr_fd("minishell: unset: Invalid identifier\n", 2);
		free(to_find);
		i++;
	}
}
