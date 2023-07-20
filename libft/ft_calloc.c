/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:11:59 by macote            #+#    #+#             */
/*   Updated: 2023/07/20 13:34:24 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	total;
	size_t	i;

	i = 0;
	total = size * count;
	ptr = NULL;
	while (!ptr)
		ptr = malloc(total);
	while (i < total)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
