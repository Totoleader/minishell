/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:31:18 by macote            #+#    #+#             */
/*   Updated: 2023/02/21 11:13:43 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*return_adress;
	int		i;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i])
	{
		i++;
	}
	return_adress = malloc(sizeof(*return_adress) * (i + 1));
	if (!return_adress)
	{
		return (NULL);
	}
	i = 0;
	while (src[i])
	{
		return_adress[i] = src[i];
		i++;
	}
	return_adress[i] = '\0';
	return (return_adress);
}

// int main(void)
// {
// 	char string[] = "abcdefg";

// 	ft_strdup(string);
// 	printf("%s", ft_strdup(string));
// 	// free(ft_strdup(string));
// 	return (0);
// }