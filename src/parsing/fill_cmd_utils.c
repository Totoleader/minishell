/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:35:28 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/17 13:45:02 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*parse_error(void)
{
	g_error_code = 258;
	ft_putstr_fd("Parse error\n", 2);
	return (NULL);
}

void	*clean_exit(t_commands *cmds)
{
	t_commands	*next;
	int			i_args;

	i_args = -1;
	while (cmds != NULL)
	{
		while (cmds->args && cmds->args[++i_args])
			free(cmds->args);
		i_args = -1;
		next = cmds->next;
		free(cmds);
		cmds = next;
	}
	return (NULL);
}

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens->arg && tokens->type != PIPE)
	{
		if (tokens->type >= REDIR_IN && tokens->type <= REDIR_OUT_APPEND)
		{
			tokens += 2;
			continue ;
		}
		else
			count++;
		tokens++;
	}
	return (count);
}

/**
 * Returns -1 if parse error
 **/
int	count_cmds(t_token *tokens)
{
	int	count;

	count = 1;
	while (tokens->arg)
	{
		if ((tokens->type >= REDIR_IN && tokens->type <= REDIR_OUT_APPEND)
			&& (tokens + 1)->type != TEXT)
			return (-1);
		if (tokens->type == PIPE && ((tokens + 1)->type == PIPE || !(tokens
					+ 1)->arg))
			return (-1);
		if (tokens->type == PIPE)
			count++;
		tokens++;
	}
	return (count);
}

t_commands	*new_cmd(void)
{
	t_commands	*new;

	new = malloc(sizeof(t_commands));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_commands));
	new->infile_fd = -1;
	new->outfile_fd = -1;
	return (new);
}
