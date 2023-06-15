/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:43:06 by macote            #+#    #+#             */
/*   Updated: 2023/02/28 15:29:54 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*return_string;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	return_string = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!return_string)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
	{
		return_string[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		return_string[i] = s2[j];
		i++;
		j++;
	}
	return_string[i] = '\0';
	return (return_string);
}

// int main(void)
// {
// 	printf("%s", ft_strjoin("abc", "defg"));
// }