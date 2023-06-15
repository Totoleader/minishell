/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:09:37 by macote            #+#    #+#             */
/*   Updated: 2023/02/21 11:22:41 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (((s1[i] != '\0') && (s2[i] != '\0')) && (i < n))
	{
		if (s1[i] != s2[i])
			return ((unsigned const char)s1[i] - (unsigned const char)s2[i]);
		i++;
	}
	if ((s1[i] == '\0' ^ s2[i] == '\0') && (i < n))
		return ((unsigned const char)s1[i] - (unsigned const char)s2[i]);
	return (0);
}

// int main(void)
// {
// 	printf("%d\n", (ft_strncmp("test\200", "test\0", 6)));
// 	return (0);
// }
