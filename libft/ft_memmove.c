/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:54:44 by macote            #+#    #+#             */
/*   Updated: 2023/02/21 11:11:04 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_str;
	const char	*src_str;
	size_t		i;

	if (!dst || !src)
		return (NULL);
	dst_str = dst;
	src_str = src;
	if (dst > src)
	{
		while (len--)
			dst_str[len] = src_str[len];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			dst_str[i] = src_str[i];
			i++;
		}
	}
	return (dst);
}

// int main(void)
// {
// 	char str1[10] = "12345678";
// 	char *str2 = str1 + 2;

// 	printf("%s\n%s\n", str1, str2);
// 	ft_memmove(str1, &str1[2], 4);
// 	printf("%s\n%s\n", str1, str2);

// }
