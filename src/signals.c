/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:59:46 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/14 13:36:50 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_interactive(int signo)
{
	(void)signo;
	g_error_code = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		g_error_code = 1;
		write(1, "\n", 1);
		exit(1);
	}
}

void	init_sighandler(int state)
{
	if (state == INTERACTIVE)
	{
		signal(SIGINT, sig_interactive);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (state == HEREDOC)
	{
		signal(SIGINT, sig_heredoc);
		signal(SIGQUIT, sig_heredoc);
	}
}
