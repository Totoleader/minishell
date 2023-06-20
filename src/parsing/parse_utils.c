/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:20:09 by macote            #+#    #+#             */
/*   Updated: 2023/06/19 15:15:17 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *alloc_copy(char *str)
{
	int i;
	char *out;
	char quote;

	i = 0;
	while (str[i] != '\0' && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != ' ')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i++];
			if (!ft_strchr(&str[i], quote))
			{
				printf("quotes not closed");
				exit(0);
			}
			while (str[i] != quote)
				i++;
		}
		i++;
	}
	if (str[0] == '>' && str[1] && str[1] == '>')
		i = 2;
	else if (str[0] == '<' && str[1] && str[1] == '<')
		i = 2;
	else if (str[0] == '>')
		i = 1;
	else if (str[0] == '<')
		i = 1;
	else if (str[0] == '|')
		i = 1;
	out = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(out, str, i + 1);
	return (out);
}