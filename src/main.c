/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 08:52:54 by macote            #+#    #+#             */
/*   Updated: 2023/07/14 15:56:19 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_error_code;

//Higher logic level of the project is here
// 1. take input
// 2. parse input (to tokens)
// 3. parse input (to commands)
// 4. execute command
// 5. go back to 1.
void	minishell(t_minishell *mini)
{
	t_token		*tokens;
	char		*input;
	t_commands	*cmds;
	while (TRUE)
	{
		cmds = NULL;
		init_sighandler(INTERACTIVE);
		input = readline("minishell $ ");
		if (!input)
		{
			free_all(cmds, mini);
			exit(0);
		}
		if (input && *input)
			add_history(input);
		tokens = parse_input(input, mini);
		cmds = fill_cmd(tokens);
		exec_cmd_master(cmds, mini);
		free_cmds(cmds);
	}
	free_mini(mini);
}

//entry of the program
int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;

	(void)argc;
	(void)argv;
	mini = init_minishell(envp);
	printf("\033[31mWelcome to minishell :)\n\n\033[0m");
	minishell(mini);
	return (0);
}
