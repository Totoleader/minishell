/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:59:46 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/20 14:01:06 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_interactive(int signo)
{
	(void)signo;
	g_error_code = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sig_heredoc(int signo)
{
	t_minishell	*mini;

	if (signo == SIGINT)
	{
		mini = init_minishell(NULL);
		g_error_code = 1;
		write(1, "\n", 1);
		close(mini->hd_fd);
		close(mini->std_bak[IN]);
		close(mini->std_bak[OUT]);
		free_cmds(mini->cmds);
		free_mini(mini);
		exit(EXIT_FAILURE);
	}
}

static void	sig_exec(int signo)
{
	if (signo == SIGQUIT)
		write(1, "Quit\n", 5);
	else if (signo == SIGINT)
		printf("\n");
}

void	init_sighandler(int state)
{
	if (state == INTERACTIVE)
	{
		signal(SIGINT, sig_interactive);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (state == EXEC)
	{
		signal(SIGINT, sig_exec);
		signal(SIGQUIT, sig_exec);
	}
	else if (state == HEREDOC)
	{
		signal(SIGINT, sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (state == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
