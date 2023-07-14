/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:15:13 by macote            #+#    #+#             */
/*   Updated: 2023/07/14 15:24:00 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//checks if there is unclosed quotes in exec_cmd_master()
static int	quote_error(void)
{
	if (g_error_code == -99)
	{
		g_error_code = 1;
		printf("error: quotes not closed.\n");
		return (TRUE);
	}
	return (FALSE);
}

//nor helper that does end of loop operations in exec_cmd_master()
void	prep_next_cmd(t_commands **cmd, int *std_backup, int *is_not_first)
{
	if ((*cmd)->type_in == REDIR_IN_DELIM)
		unlink(TEMP_FILE);
	(*is_not_first)++;
	(*cmd) = (*cmd)->next;
	reset_std_in_out(std_backup);
}

//norm helper that init vars in exec_cmd_master()
int	init_vars(t_commands **current, t_commands *cmds, int *is_not_first)
{
	if (quote_error())
		return (FALSE);
	(*current) = cmds;
	*is_not_first = 0;
	return (TRUE);
}

//norm helper closes std backups in exec_cmd_master()
void	close_std_backups(int *std_backup)
{
	close(std_backup[IN]);
	close(std_backup[OUT]);
}
