/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:23:15 by macote            #+#    #+#             */
/*   Updated: 2023/02/21 11:16:55 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*return_string;

	if (!s || !f)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	return_string = malloc(sizeof(char) * (i + 1));
	if (!return_string)
		return (NULL);
	i = 0;
	while (s[i])
	{
		return_string[i] = f(i, s[i]);
		i++;
	}
	return_string[i] = '\0';
	return (return_string);
}
