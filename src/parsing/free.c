/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:05:04 by macote            #+#    #+#             */
/*   Updated: 2023/07/14 13:34:13 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmds(t_commands *cmds)
{
	t_commands	*current;
	t_commands	*to_free;
	int			i;

	if (!cmds)
		return ;
	current = cmds;
	while (current)
	{
		i = 0;
		to_free = current;
		if (current->args)
		{
			while (current->args[i])
				free(current->args[i++]);
			free(current->args);
		}
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		current = current->next;
		free(to_free);
	}
}

void	free_mini(t_minishell *mini)
{
	ft_lstclear_content(&mini->env);
	free(mini);
}

void	free_all(t_commands *cmds, t_minishell *mini)
{
	free_cmds(cmds);
	free_mini(mini);
	mini = NULL;
	rl_clear_history();
}
