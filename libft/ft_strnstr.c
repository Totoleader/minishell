/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:50:15 by macote            #+#    #+#             */
/*   Updated: 2023/02/21 11:17:55 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*helper(int i, const char *str, const char *to_find)
{
	int	j;

	j = 0;
	while (to_find[j] != '\0')
	{
		if (str[i] != to_find[j])
		{
			return (NULL);
		}
		i++;
		j++;
	}
	return ((char *)&str[i - j]);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;

	if (!needle || !haystack)
		return (NULL);
	i = 0;
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[i] != '\0' && len > 0)
	{
		if ((haystack[i] == needle[0]) && (helper(i, haystack, needle) != NULL
				&& (ft_strlen(needle) <= len)))
		{
			return (helper(i, haystack, needle));
		}
		i++;
		len--;
	}
	return (NULL);
}

// int main()
// {
// 	char string[] = "";
// 	char find[] = "abc";
// 	char *str;

// 		if (!(ft_strnstr("lorem ipsum dolor sit amet", "dolor", 15)))
//         printf("NULL");
//     else
//         printf("%s", ft_strnstr("lorem ipsum dolor sit amet", "dolor", 15));

// 	// printf("%s\n", ft_strnstr(string, find, 5));
// 	// printf("%s", strstr(string, find));

// 	return (0);
// }
