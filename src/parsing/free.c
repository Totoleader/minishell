/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:05:04 by macote            #+#    #+#             */
/*   Updated: 2023/07/24 10:23:00 by scloutie         ###   ########.fr       */
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

static void	free_helper(t_token *token, t_list *vars)
{
	int		i;
	t_list	*current;
	char	*temp;

	current = vars;
	temp = token->arg;
	i = 0;
	while (current && ft_strnstr(temp, "$?", ft_strlen(temp)))
	{
		while (*temp && *temp != '$')
			temp++;
		if (!ft_strncmp(temp, "$?", 2))
		{
			temp = temp + 2;
			free(current->content);
			current = current->next;
		}
		else
		{
			temp++;
			if (*temp != '$')
				current = current->next;
		}
	}
}

void	clear_vars(t_token *token, t_list *vars, t_count *c, char *new_content)
{
	free(c);
	free_helper(token, vars);
	ft_lstclear(&vars);
	free(token->arg);
	token->arg = new_content;
}
