/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:42:26 by scloutie          #+#    #+#             */
/*   Updated: 2023/06/22 13:08:07 by macote           ###   ########.fr       */
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
	new->infile_fd = -1;
	new->outfile_fd = -1;
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

int	set_cmd(t_commands **command, t_token *tok, char file)
{
	if (!tok->arg || tok->type != TEXT)
	{
		ft_putstr_fd("Parse error\n", 2);
		return (0);
	}
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
	return (1);
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
			if (!tokens[i_tok + 1].arg)
			{
				ft_putstr_fd("Parse error\n", 2);
				return (clean_exit(first));
			}
			new_cmd(&cmds);
			cmds = cmds->next;
			i_tok++;
			continue ;
		}
		else if (tokens[i_tok].type == TEXT)
			i_tok += (fill_args(&cmds, &tokens[i_tok]) - 1);
		else if ((tokens[i_tok].type == REDIR_IN || tokens[i_tok].type == REDIR_IN_DELIM))
		{
			if (!set_cmd(&cmds, &tokens[++i_tok], 'I'))
				return (clean_exit(first));
		}
		else if ((tokens[i_tok].type == REDIR_OUT || tokens[i_tok].type == REDIR_OUT_APPEND))
		{
			if (!set_cmd(&cmds, &tokens[++i_tok], 'O'))
				return (clean_exit(first));
		}
		i_tok++;
	}
	// cmds = first;
	// while (cmds)
	// {
	// 	printf("---------------------\n");
	// 	printf("Command: ");
	// 	for (int i = 0; cmds->args && cmds->args[i]; i++)
	// 		printf("%s ", cmds->args[i]);
	// 	printf("\n");
	// 	printf("infile: %s\n", cmds->infile);
	// 	printf("outfile: %s\n", cmds->outfile);
	// 	cmds = cmds->next;
	// }

	return (first);
}
