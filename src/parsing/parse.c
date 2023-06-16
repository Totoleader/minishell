/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:03:12 by macote            #+#    #+#             */
/*   Updated: 2023/06/16 12:17:03 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//adds the beginning of the arg to the linked list
static void find_start_of_arg(char *input, int *i, t_list **tokens)
{
	while (input[(*i)] == ' ')
		(*i)++;
	ft_lstadd_back(tokens, ft_lstnew(&input[(*i)]));
}

//null terminates the arg
static void find_end_of_arg(char *input, int *i)
{
	char quote;

	while (input[(*i)] && input[(*i)] != ' ')
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
	if (input[(*i)])
			input[(*i)++] = '\0';
}

//puts each arg into a node in a linked list
static void	parse_to_list(char *input, t_list **tokens)
{
	int	i;
	
	i = 0;
	if (!input[i])
		ft_lstadd_back(tokens, ft_lstnew(""));
	while (input[i])
	{
		find_start_of_arg(input, &i, tokens);
		find_end_of_arg(input, &i);
	}
}

//transfers args from linked list to "t_input command" struct
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

	i = 0;
	while (current)
	{
		command.args[i++] = current->content;
		current = current->next;
	}
	ft_lstclear(&tokens);
	return (command);
}
