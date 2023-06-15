/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:03:12 by macote            #+#    #+#             */
/*   Updated: 2023/06/15 14:53:45 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int not_end_of_arg(char *input, int *i)
// {
// 	if (input[(*i)] && input[(*i)] != ' '
// 		&& input[(*i)] != '\"' && input[(*i)] != '\'')
// 		return (TRUE);
// 	return (FALSE);
// }

// int	parse_quotes(char *input, t_list **tokens, char c, int *i, int *destroyed_quote)
// {
// 	int starts_with_quote;

// 	starts_with_quote = input[(*i)] == c || *destroyed_quote;
	
// 	if (starts_with_quote && !ft_strchr(&input[(*i) + 1], c))
// 	{
// 		//$$$$$$$$$$$$$$$$$$$$$variable globale code d'erreur?$$$$$$$$$$$$$$$$$$$$$$$$$
// 		printf("\nquotes not ended\n");
// 		exit(1);
// 	}
// 	else if (starts_with_quote)
// 	{
// 		if (!(*destroyed_quote))
// 			(*i)++;
// 		ft_lstadd_back(tokens, ft_lstnew(&input[(*i)], TRUE));
// 		while (input[(*i)] != c)
// 			(*i)++;
// 		input[(*i)] = '\0';
// 		(*i)++;
// 		*destroyed_quote = FALSE;
// 		return (TRUE);
// 	}
// 	return (FALSE);
// }

// void	parse_no_quotes(char *input, t_list **tokens, int *i, int *destroyed_quote)
// {
// 	ft_lstadd_back(tokens, ft_lstnew(&input[(*i)], FALSE));
// 	while (not_end_of_arg(input, i))
// 		(*i)++;
// 	if (input[(*i)] == '\'' || input[(*i)] == '\"')
// 		*destroyed_quote = TRUE;
// 	input[(*i)++] = '\0';
// }

void	parse_to_list(char *input, t_list **tokens)
{
	int	i;
	int destroyed_quote;
	
	destroyed_quote = FALSE;
	i = 0;
	if (!input[i])
		ft_lstadd_back(tokens, ft_lstnew("", FALSE));
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!parse_quotes(input, tokens, '\"', &i, &destroyed_quote) && !parse_quotes(input,
				tokens, '\'', &i, &destroyed_quote))
		{
			parse_no_quotes(input, tokens, &i, &destroyed_quote);
		}
	}
}



t_input	parse_input(char *input)
{
	t_list	*tokens;
	t_input	command;
	t_list	*current;
	int i;

	tokens = NULL;
	parse_to_list(input, &tokens);
	
	current = tokens;
	command.command = current->content;
	
	current = current->next;
	command.args = ft_calloc(sizeof(char *), ft_lstsize(current) + 1);
	command.quoted = ft_calloc(sizeof(int), ft_lstsize(current) + 1);
	
	i = 0;
	while (current)
	{
		command.quoted[i] = current->quoted;
		command.args[i++] = current->content;
		current = current->next;
	}
	
	return (command);
}
