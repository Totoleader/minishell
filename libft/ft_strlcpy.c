/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:36:18 by macote            #+#    #+#             */
/*   Updated: 2023/02/21 16:00:50 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && (dstsize - 1) > 0)
		{
			dst[i] = src[i];
			i++;
			dstsize--;
		}
		dst[i] = '\0';
	}
	i = 0;
	while (src[i])
		i++;
	return (i);
}

// int main(void)
// {
// 	char source[] = "lorem ipsum dolor sit amet";
// 	char dest[] = "xyzljkdsflkasdf";
// 	printf("%s\n", dest);
// 	ft_strlcpy(dest, source, 0);
// 	// strlcpy(dest, source, 15);

// 	printf("%s", dest);

// }
