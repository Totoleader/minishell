/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:21:51 by macote            #+#    #+#             */
/*   Updated: 2023/07/14 15:28:01 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//echo builtin
void	echo_(char **args)
{
	int	i;
	int	flag_is_active;

	flag_is_active = FALSE;
	g_error_code = 0;
	i = 0;
	if (!args[0])
	{
		printf("\n");
		return ;
	}
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
