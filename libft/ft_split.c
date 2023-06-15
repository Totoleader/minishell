/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:48:44 by macote            #+#    #+#             */
/*   Updated: 2023/02/22 09:45:33 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**empty_words(char const *s, char c)
{
	int		words;
	int		i;
	char	**empty_array_words;

	words = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')))
			words++;
		i++;
	}
	empty_array_words = malloc(sizeof(char *) * (words + 1));
	if (!empty_array_words)
		return (NULL);
	empty_array_words[words] = NULL;
	return (empty_array_words);
}

int	count_chars(char const *s, char c)
{
	int	chars;

	chars = 0;
	while (*s)
	{
		if (*s != c)
		{
			chars++;
			if (*(s + 1) == c || *(s + 1) == '\0')
				break ;
		}
		s++;
	}
	return (chars);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char	**fill_array(char const *s, char c, char **array)
{
	int	i;
	int	j;
	int	chars;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			j = 0;
			chars = count_chars(s, c);
			array[i] = malloc(sizeof(char) * (chars + 1));
			if (!array[i])
			{
				free_array(array);
				return (NULL);
			}
			while (*s && *s != c)
				array[i][j++] = *s++;
			array[i++][j] = '\0';
		}
		else
			s++;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = empty_words(s, c);
	if (!array)
		return (NULL);
	return (fill_array(s, c, array));
}

// int	main(void)
// {
// 	// int i;
// 	// i = 0;
// 	// while (i < 1)
// 	// {
// 	// 	printf("%s\n", ft_split("", '\0')[i]);
// 	// 	i++;
// 	// }
// 	// printf("%s", ft_split("abc de f g", ' ')[0]);

// 				// ' ')[0]);
// 	printf("%s", ft_split("  lorem  ipsum  ", ' ')[1]);
// 	return (0);
// }
