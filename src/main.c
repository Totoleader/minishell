/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 08:52:54 by macote            #+#    #+#             */
/*   Updated: 2023/06/16 13:52:47 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell(void)
{
	t_token *tokens;
	char *input;
	
	// while (TRUE)
	// {
	// 	input = readline("\033[31mminishell $ \033[0m");
		input = ft_calloc(sizeof(char), 100);
		// ft_strlcpy(input, "allo 123 \"123456 abc\" \'kjlahsdfljhasdlfhadlwhfhil\' ", 55);
		ft_strlcpy(input, "123 \"123 \"123  cat >  <<  >>  >>1  >1 || |", 55);
		tokens = parse_input(input);
		execute_command(tokens);
	// }
	
}

int main(void)
{
	printf("\033[31mWelcome to minishell :)\n\n\033[0m");
	minishell();
	
	return (0);
}
