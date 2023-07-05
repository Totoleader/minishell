/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:21:51 by macote            #+#    #+#             */
/*   Updated: 2023/07/05 12:35:38 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_(char **args)
{
	int	i;
	int	flag_is_active;

	flag_is_active = FALSE;
	i = 0;
	if (!ft_strncmp(args[0], "-n", 3))
	{
		flag_is_active = TRUE;
		i++;
	}
	while (args[i])
	{
		if (i && ft_strncmp(args[0], "-n", 3))
			printf(" ");
		printf("%s", args[i]);
		i++;
	}
	if (!flag_is_active)
		printf("\n");
}
