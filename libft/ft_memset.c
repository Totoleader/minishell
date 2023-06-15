/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:03:29 by macote            #+#    #+#             */
/*   Updated: 2023/02/21 11:20:31 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int				i;
	unsigned char	*set_str;

	if (!b)
		return (NULL);
	set_str = b;
	i = 0;
	while (len-- > 0)
		set_str[i++] = (unsigned char)c;
	return (b);
}
