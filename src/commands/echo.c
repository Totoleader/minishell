/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:21:51 by macote            #+#    #+#             */
/*   Updated: 2023/06/15 13:29:59 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	should_print_space_before(t_input command, int i)
{
	if (i != 0 && (*(command.args[i] - 1) == ' ' || (*(command.args[i]
					- 1) == '\0' && !command.quoted[i - 1])
			|| (command.quoted[i] && (*(command.args[i] - 1) == '\''
					|| *(command.args[i] - 1) == '\"'))))
		return (TRUE);
	return (FALSE);
}

void	echo_(t_input command)
{
	int	i;

	i = 0;
	// if (command.quoted[0] && *(command.args[0] - 2) != ' ' && *(command.args[0]
	// 		- 2) != '\0')
	// {
	// 	printf("error command not found\n");
	// 	return ;
	// }
	while (command.args[i])
	{
		if (should_print_space_before(command, i))
			printf(" ");
		printf("%s", command.args[i++]);
	}
	printf("\n");
}
