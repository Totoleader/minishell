/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:42:26 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/13 12:36:24 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	fill_args(t_commands **command, t_token *tokens)
// {
// 	char	**args;
// 	int		i;
// 	int		j;

// 	j = -1;
// 	args = malloc(sizeof(char *) * (count_args(tokens) + 1));
// 	if (!args)
// 		exit(1); /* free */
// 	i = 0;
// 	while (tokens->type == TEXT)
// 	{
// 		args[i] = tokens->arg;
// 		if (i == 0)
// 		{
// 			while (args[0][++j])
// 				args[0][j] = ft_tolower(args[0][j]);
// 		}
// 		tokens++;
// 		i++;
// 	}
// 	args[i] = NULL;
// 	(*command)->args = args;
// 	return (i);
// }

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

	out = NULL;
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
		if (tokens->type == PIPE)
		{
			free(tokens->arg);
			tokens++;
		}
	}
	//free(tokens);
	return (out);
}

// t_commands	*fill_cmd(t_token *tokens)
// {
// 	t_commands	*first;
// 	t_commands	*cmds;
// 	int			i_tok;

// 	cmds = NULL;
// 	new_cmd(&cmds);
// 	first = cmds;
// 	i_tok = 0;
// 	while (tokens[i_tok].arg != NULL)
// 	{
// 		if (tokens[i_tok].type == PIPE)
// 		{
// 			free(tokens[i_tok].arg);
// 			if (!tokens[i_tok + 1].arg)
// 			{
// 				error_code = 258;
// 				ft_putstr_fd("Parse error\n", 2);
// 				return (clean_exit(first));
// 			}
// 			new_cmd(&cmds);
// 			cmds = cmds->next;
// 			i_tok++;
// 			continue ;
// 		}
// 		else if (tokens[i_tok].type == TEXT)				// ls -l > grep 2 > outfile => interprete "2" comme un autre argument de ls. il faut compter les tokens TEXT qui ne sont pas apres une redirection jusqu'a ce quon rencontre un pipe pour trouve le bon nombre d'argument
// 			i_tok += (fill_args(&cmds, &tokens[i_tok]) - 1);
// 		else if ((tokens[i_tok].type == REDIR_IN || tokens[i_tok].type == REDIR_IN_DELIM))
// 		{
// 			free(tokens[i_tok].arg);
// 			if (!set_cmd(&cmds, &tokens[++i_tok], 'I'))
// 				return (clean_exit(first));
// 		}
// 		else if ((tokens[i_tok].type == REDIR_OUT || tokens[i_tok].type == REDIR_OUT_APPEND))
// 		{
// 			free(tokens[i_tok].arg);
// 			if (!set_cmd(&cmds, &tokens[++i_tok], 'O'))
// 				return (clean_exit(first));
// 		}
// 		i_tok++;
// 	}
// 	free(tokens);
// 	return (first);
// }
