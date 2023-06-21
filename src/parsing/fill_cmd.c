/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:42:26 by scloutie          #+#    #+#             */
/*   Updated: 2023/06/20 11:01:00 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_cmd(t_commands **cmds)
{
	t_commands	*new;

	new = malloc(sizeof(t_commands));
	if (!new)
		exit(1); /* free */
	ft_memset(new, 0, sizeof(t_commands));
	if (*cmds == NULL)
		*cmds = new;
	else
		(*cmds)->next = new;
}

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens->type == TEXT)
	{
		count++;
		tokens++;
	}
	return (count);
}

int	fill_args(t_commands **command, t_token *tokens)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (count_args(tokens) + 1));
	if (!args)
		exit(1); /* free */
	i = 0;
	while (tokens->type == TEXT)
	{
		args[i] = tokens->arg;
		tokens++;
		i++;
	}
	args[i] = NULL;
	(*command)->args = args;
	return (i);
}

void	set_cmd(t_commands **command, t_token *tok, char file)
{
	if (file == 'I')
	{
		(*command)->infile = tok->arg;
		(*command)->type_in = (tok - 1)->type;
	}
	else if (file == 'O')
	{
		(*command)->outfile = tok->arg;
		(*command)->type_out = (tok - 1)->type;
	}
}

t_commands	*fill_cmd(t_token *tokens)
{
	t_commands	*first;
	t_commands	*cmds;
	int			i_tok;

	cmds = NULL;
	new_cmd(&cmds);
	first = cmds;
	i_tok = 0;
	while (tokens[i_tok].arg != NULL)
	{
		if (tokens[i_tok].type == PIPE)
		{
			new_cmd(&cmds);
			cmds = cmds->next;
			i_tok++;
			continue ;
		}
		else if (tokens[i_tok].type == TEXT)
			i_tok += (fill_args(&cmds, &tokens[i_tok]) - 1);
		else if ((tokens[i_tok].type == REDIR_IN || tokens[i_tok].type == REDIR_IN_DELIM) && tokens[i_tok + 1].arg)
			set_cmd(&cmds, &tokens[++i_tok], 'I');
		else if ((tokens[i_tok].type == REDIR_OUT || tokens[i_tok].type == REDIR_OUT_APPEND) && tokens[i_tok + 1].arg)
			set_cmd(&cmds, &tokens[++i_tok], 'O');
		i_tok++;
	}
	// while (first)
	// {
	// 	printf("%s\n", *first->args);
	// 	printf("%s\n", first->infile);
	// 	printf("%s\n", first->outfile);
	// 	printf("%d\n", first->type_in);
	// 	printf("%d\n\n", first->type_out);
	// 	first = first->next;
	// }
	
	return (first);
}
