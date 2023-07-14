/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:42:26 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/14 14:06:56 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_cmd(t_commands **command, t_token **tok, char file)
{
	if (file == 'I')
	{
		(*command)->infile = (*tok + 1)->arg;
		(*command)->type_in = (*tok)->type;
	}
	else if (file == 'O')
	{
		(*command)->outfile = (*tok + 1)->arg;
		(*command)->type_out = (*tok)->type;
	}
	free((*tok)->arg);
	(*tok) += 2;
	return (1);
}

t_token	*get_command(t_commands **cmds, t_token *tokens, int n_args)
{
	t_commands	*new;
	int			i_cmd;

	new = new_cmd(cmds);
	if (!new)
		return (clean_exit(*cmds));
	i_cmd = -1;
	new->args = malloc(sizeof(char *) * (n_args + 1));
	if (!new->args)
		return (clean_exit(*cmds));
	while (tokens->arg && tokens->type != PIPE)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_IN_DELIM)
			set_cmd(&new, &tokens, 'I');
		else if (tokens->type == REDIR_OUT || tokens->type == REDIR_OUT_APPEND)
			set_cmd(&new, &tokens, 'O');
		else if (tokens->type == TEXT)
		{
			new->args[++i_cmd] = tokens->arg;
			tokens++;
		}
	}
	if (i_cmd != -1)
		new->args[++i_cmd] = NULL;
	return (tokens);
}

t_commands	*fill_cmd(t_token *tokens)
{
	t_commands	*out;
	int			n_cmds;
	int			n_args;
	int			i;
	t_token		*first;

	out = NULL;
	first = tokens;
	n_cmds = count_cmds(tokens);
	if (n_cmds == -1)
		return (parse_error());
	i = -1;
	while (++i < n_cmds)
	{
		n_args = count_args(tokens);
		tokens = get_command(&out, tokens, n_args);
		if (!tokens)
			return (clean_exit(out));
		if (tokens->type == PIPE && ++tokens)
			free((tokens - 1)->arg);
	}
	free(first);
	return (out);
}
