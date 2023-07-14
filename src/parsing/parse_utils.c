/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:20:09 by macote            #+#    #+#             */
/*   Updated: 2023/07/14 14:28:04 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//helper to alloc_copy()
static void	alloc_copy_special_cases(char *str, int *i)
{
	if (str[0] == '>' && str[1] && str[1] == '>')
		*i = 2;
	else if (str[0] == '<' && str[1] && str[1] == '<')
		*i = 2;
	else if (str[0] == '>')
		*i = 1;
	else if (str[0] == '<')
		*i = 1;
	else if (str[0] == '|')
		*i = 1;
}

//reallocate and copy a string without the quotes
char	*alloc_copy(char *str)
{
	int		i;
	char	*out;
	char	quote;

	i = 0;
	while (str[i] != '\0' && str[i] != '>' && str[i] != '<' && str[i] != '|'
		&& str[i] != ' ')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i++];
			if (!ft_strchr(&str[i], quote))
				g_error_code = -99;
			while (str[i] != quote)
				i++;
		}
		i++;
	}
	alloc_copy_special_cases(str, &i);
	out = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(out, str, i + 1);
	return (out);
}
