/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:41:55 by macote            #+#    #+#             */
/*   Updated: 2023/02/22 09:45:58 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include "ft_strlen.c"
// #include <stdio.h>

char	*return_string(char const *s1, int removed_chars)
{
	size_t	i;
	int		size;
	char	*return_string;

	size = ft_strlen(s1) - removed_chars;
	if (size < 0)
		size = 0;
	return_string = malloc(sizeof(char) * (size + 1));
	if (!return_string)
		return (NULL);
	i = 0;
	while (i < (size_t)size)
	{
		return_string[i] = s1[i];
		i++;
	}
	return_string[i] = 0;
	return (return_string);
}

char	*trimmer(char const *s1, char const *set, int reset_required,
		int s1_len)
{
	int	i;
	int	j;
	int	removed_chars;

	removed_chars = 0;
	i = -1;
	j = 0;
	while (set[++i] && s1[j])
	{
		reset_required = 0;
		if (s1[j] == set[i])
		{
			j++;
			reset_required = 1;
		}
		if ((s1_len >= 1) && (s1[s1_len - 1] == set[i]))
		{
			s1_len--;
			removed_chars++;
			reset_required = 1;
		}
		if (reset_required)
			i = -1;
	}
	return (return_string((s1 + j), removed_chars));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	s1_len;
	int	reset_required;

	if (!s1 || !set)
		return (NULL);
	reset_required = 0;
	s1_len = ft_strlen(s1);
	return (trimmer(s1, set, reset_required, s1_len));
}

// int main(void)
// {
// 	printf("%s", ft_strtrim(" . abcd", " "));
// 	return (0);
// }
