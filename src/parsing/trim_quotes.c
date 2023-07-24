/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:31:47 by macote            #+#    #+#             */
/*   Updated: 2023/07/24 10:51:36 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//helper to the trimmer() function
static int	count_strings(t_token *token)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (token->arg[i])
	{
		if (token->arg[i] == '\"' || token->arg[i] == '\'')
		{
			quote = token->arg[i];
			i++;
			while (token->arg[i] && token->arg[i] != quote && ++i)
				count++;
			i++;
		}
		if (token->arg[i] && token->arg[i] != '\"' && token->arg[i] != '\'')
		{
			count++;
			i++;
		}
	}
	return (count);
}

//trims the content of the tokens and by reallocating and doing a copy
void	trimmer(t_token *token)
{
	int		i;
	int		count;
	char	quote;
	char	*trimmed_string;

	count = count_strings(token);
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
