/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:03:12 by macote            #+#    #+#             */
/*   Updated: 2023/07/14 14:28:10 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//adds the beginning of the arg to the linked list
static void	find_start_of_arg(char *input, int *i, t_list **tokens)
{
	while (input[(*i)] == ' ')
		(*i)++;
	if (input[(*i)])
		ft_lstadd_back(tokens, ft_lstnew(alloc_copy(&input[(*i)])));
}

//null terminates the arg
static void	*find_end_of_arg(char *input, int *i)
{
	char	quote;

	if (input[(*i) + 1] && ((input[(*i)] == '>' && input[(*i) + 1] == '>')
			|| (input[(*i)] == '<' && input[(*i) + 1] == '<')))
	{
		(*i) = (*i) + 2;
		return (NULL);
	}
	else if (input[(*i)] == '|' || input[(*i)] == '<' || input[(*i)] == '>')
		return ((*i)++, NULL);
	while (input[(*i)] && input[(*i)] != ' ' && input[(*i)] != '|'
		&& input[(*i)] != '<' && input[(*i)] != '>')
	{
		if (input[(*i)] == '\"' || input[(*i)] == '\'')
		{
			quote = input[(*i)++];
			if (!ft_strchr(&input[(*i)], quote))
				g_error_code = -99;
			while (input[(*i)] != quote)
				(*i)++;
		}
		(*i)++;
	}
	return (NULL);
}

//puts each arg into a node in a linked list
static void	parse_to_list(char *input, t_list **tokens)
{
	int	i;

	i = 0;
	while (input[i])
	{
		find_start_of_arg(input, &i, tokens);
		find_end_of_arg(input, &i);
	}
	free(input);
}

//assigns the type of the token so it can easily manipulated
void	assign_type(t_token *token)
{
	if (!ft_strncmp(token->arg, "<", 2))
		token->type = REDIR_IN;
	else if (!ft_strncmp(token->arg, ">", 2))
		token->type = REDIR_OUT;
	else if (!ft_strncmp(token->arg, "<<", 3))
		token->type = REDIR_IN_DELIM;
	else if (!ft_strncmp(token->arg, ">>", 3))
		token->type = REDIR_OUT_APPEND;
	else if (!ft_strncmp(token->arg, "|", 2))
		token->type = PIPE;
	else
		token->type = TEXT;
}

//transfers args from linked list to "t_input command" struct
t_token	*parse_input(char *input, t_minishell *mini)
{
	t_list	*args;
	t_token	*tokens;
	t_list	*current;
	int		i;

	args = NULL;
	parse_to_list(input, &args);
	current = args;
	tokens = calloc(sizeof(t_token), ft_lstsize(args) + 1);
	i = 0;
	while (current)
	{
		tokens[i].arg = current->content;
		assign_type(&tokens[i]);
		interpret_dollar_signs(&tokens[i], mini);
		trimmer(&tokens[i]);
		i++;
		current = current->next;
	}
	tokens[i].arg = NULL;
	ft_lstclear(&args);
	return (tokens);
}
