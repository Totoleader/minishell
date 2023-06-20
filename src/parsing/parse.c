/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:03:12 by macote            #+#    #+#             */
/*   Updated: 2023/06/20 10:25:24 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//adds the beginning of the arg to the linked list
static void find_start_of_arg(char *input, int *i, t_list **tokens)
{
	while (input[(*i)] == ' ')
		(*i)++;
	if (input[(*i)])
		ft_lstadd_back(tokens, ft_lstnew(alloc_copy(&input[(*i)])));
}

//null terminates the arg
static void find_end_of_arg(char *input, int *i)//some things will be broken with broken with quotes/////////////////////
{
	char quote;

	if (input[(*i) + 1] && ((input[(*i)] == '>' && input[(*i) + 1] == '>') || (input[(*i)] == '<' && input[(*i) + 1] == '<')))
	{
		(*i) = (*i) + 2;
		return ;
	}
	else if (input[(*i)] == '|' || input[(*i)] == '<' || input[(*i)] == '>')
	{
		(*i)++;
		return ;
	}
	while (input[(*i)] && input[(*i)] != ' ' && input[(*i)] != '|' && input[(*i)] != '<' && input[(*i)] != '>')
	{
		if (input[(*i)] == '\"' || input[(*i)] == '\'')
		{
			quote = input[(*i)++];
			if (!ft_strchr(&input[(*i)], quote))
			{
				printf("quotes not closed");
				exit(0);
			}
			while (input[(*i)] != quote)
				(*i)++;
		}
		(*i)++;
	}
}

//puts each arg into a node in a linked list
static void	parse_to_list(char *input, t_list **tokens)
{
	int	i;
	
	i = 0;
	// if (!input[i])
	// 	ft_lstadd_back(tokens, ft_lstnew(""));
	while (input[i])
	{
		find_start_of_arg(input, &i, tokens);
		find_end_of_arg(input, &i);
	}
	free(input);
}

void assign_type(t_token *token)
{
	if (!ft_strncmp(token->arg, "<", 2))
		token->type = REDIR_IN;
	else if (!ft_strncmp(token->arg, ">", 2))
		token->type = REDIR_OUT;
	else if (!ft_strncmp(token->arg, "<<", 3))
		token->type = REDIR_OUT_DELIM;
	else if (!ft_strncmp(token->arg, ">>", 3))
		token->type = REDIR_OUT_APPEND;
	else if (!ft_strncmp(token->arg, "|", 2))
		token->type = PIPE;
	else if (!ft_strncmp(token->arg, "$?", 3))
		token->type = LAST_COMMAND;
	else if (!ft_strncmp(token->arg, "$", 1))
		token->type = VAR_ENV;
	else
		token->type = TEXT;
}

void trimmer(t_token *token)
{
	int i;
	int count;
	char quote;
	char *trimmed_string;

	i = 0;
	count = 0;
	while (token->arg[i])
	{
		if (token->arg[i] == '\"' || token->arg[i] == '\'')
		{
			quote = token->arg[i];
			i++;
			while (token->arg[i] && token->arg[i] != quote)
			{
				count++;
				i++;
			}
			i++;
		}
		if (token->arg[i++])
			count++;
	}
	trimmed_string = ft_calloc(sizeof(char), count + 1);
	i = 0;
	count = 0;
	while (token->arg[i])
	{
		if (token->arg[i] == '\"' || token->arg[i] == '\'')
		{
			quote = token->arg[i];
			i++;
			while (token->arg[i] && token->arg[i] != quote)
				trimmed_string[count++] = token->arg[i++];
			i++;
		}
		else
			trimmed_string[count++] = token->arg[i++];
	}
	free(token->arg);
	token->arg = trimmed_string;
}

void trim_quotes(t_token **token, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		// if (ft_strchr(ft_strchr(token[i]->arg, '\"') + 1, '\"'))
		// {
		// 	/* code */
		// }
		trimmer(token[i]);
		i++;
	}
	
}

//transfers args from linked list to "t_input command" struct
t_token	*parse_input(char *input)
{
	t_list	*args;
	t_token	*tokens;
	t_list	*current;
	int i;

	args = NULL;
	parse_to_list(input, &args);
	current = args;
	tokens = calloc(sizeof(t_token), ft_lstsize(args) + 1);
	i = 0;
	while (current)
	{
		tokens[i].arg = current->content;
		assign_type(&tokens[i]);
		trimmer(&tokens[i]);
		printf("%s type:%d\n", tokens[i].arg, tokens[i].type);
		i++;
		current = current->next;
	}
	// trim_quotes(&tokens, ft_lstsize(args));
	if (args)
		ft_lstclear(&args);
	return (tokens);
}
