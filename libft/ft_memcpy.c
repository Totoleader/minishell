/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:32:49 by macote            #+#    #+#             */
/*   Updated: 2023/02/21 17:37:39 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int					i;
	const unsigned char	*set_src;
	unsigned char		*set_dst;

	if (!src && !dst)
		return (NULL);
	set_dst = dst;
	set_src = src;
	i = 0;
	while (n > 0)
	{
		set_dst[i] = set_src[i];
		n--;
		i++;
	}
	return (dst);
}

// int main(void)
// {
// 	char str1[10] = "abcdefg";
// 	char *str2 = str1 + 2;

// 	printf("%s\n%s\n", str1, str2);
// 	memcpy(str1, str2, 3);
// 	printf("%s\n%s\n", str1, str2);

// }