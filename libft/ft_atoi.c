/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:06:00 by macote            #+#    #+#             */
/*   Updated: 2023/05/23 12:11:23 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	int			i;
	int			is_negative;
	long long	resultat;

	if (!str)
		return (0);
	is_negative = 0;
	resultat = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9')
		is_negative = ++i;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		resultat = (resultat * 10) + (str[i++] - 48);
	if (str[i] || is_negative)
		return (2147483649);
	if (is_negative)
		resultat *= -1;
	return (resultat);
}
