/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:15:10 by macote            #+#    #+#             */
/*   Updated: 2023/02/21 11:31:17 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include "ft_strlen.c"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	if (!dst || !src)
		return (0);
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = dst_len;
	j = 0;
	while (src[j] && i < (dstsize - 1) && dstsize > 0)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	if (dstsize == 0 || dst_len >= dstsize)
		return (dstsize + src_len);
	else
		return (dst_len + src_len);
}

// int main(void)
// {
// 	// size_t nb = 0;

// 	char source[100] = "lorem ipsum dolor sit amet";
// 	char dest[14] = "a";
// 	// printf("%s\n", dest);
// 	// ft_strlcat(dest, source, 8);
// 	// strlcat(dest, source, 0);
// 	// printf("%s\n", dest);

// 	printf("\n%zu", ft_strlcat(dest, source, 15));
// 	// printf("\n%d", strlcat(dest, source, 1));
// }
