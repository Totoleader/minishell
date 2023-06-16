/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 08:52:54 by macote            #+#    #+#             */
/*   Updated: 2023/06/16 11:39:29 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell(void)
{
	t_input command;
	char *input;
	
	while (TRUE)
	{
		input = readline("\033[31mminishell $ \033[0m");
		// input = ft_calloc(sizeof(char), 100);
		// ft_strlcpy(input, "allo 123 \"123456 abc\" \'kjlahsdfljhasdlfhadlwhfhil\' ", 55);
		// ft_strlcpy(input, "asdf lol \"asdfasdfasdf\"asdfasdfasdf", 55);
		command = parse_input(input);
		execute_command(command);
	}
	
}

int main(void)
{
	printf("\033[31mWelcome to minishell :)\n\n\033[0m");
	minishell();
	
	return (0);
}
