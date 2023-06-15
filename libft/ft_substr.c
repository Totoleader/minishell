/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:26:46 by macote            #+#    #+#             */
/*   Updated: 2023/02/21 11:30:04 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*return_string;
	int		i;
	size_t	max_copy_len;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start <= s_len)
		max_copy_len = ft_strlen(&s[start]);
	else
	{
		len = 0;
		max_copy_len = 0;
	}
	if (max_copy_len < len)
		len = max_copy_len;
	return_string = ft_calloc(1, sizeof(char) * (len + 1));
	if (!return_string)
		return (NULL);
	i = 0;
	while (len-- && start < s_len)
		return_string[i++] = s[start++];
	return_string[i] = '\0';
	return (return_string);
}

// int main(void)
// {
// 	printf("%s", ft_substr("asdf", 1, 2));
// 	return (0);
// }
