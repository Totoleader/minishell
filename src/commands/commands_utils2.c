/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:45:34 by macote            #+#    #+#             */
/*   Updated: 2023/07/19 12:07:14 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_not_found(char *str)
{
	g_error_code = 127;
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": Command not found.\n", STDERR_FILENO);
}

//checks for file permissions
int	check_file(t_commands **cmd)
{
	if ((*cmd)->type_in != REDIR_IN_DELIM && (*cmd)->infile
		&& access((*cmd)->infile, F_OK | R_OK) != 0)
	{
		g_error_code = 1;
		printf("minishell: %s: Permission denied\n", (*cmd)->infile);
		(*cmd) = (*cmd)->next;
		return (TRUE);
	}
	else if ((*cmd)->outfile && access((*cmd)->outfile, F_OK) == 0
		&& access((*cmd)->outfile, W_OK) != 0)
	{
		g_error_code = 1;
		printf("minishell: %s: Permission denied\n", (*cmd)->outfile);
		(*cmd) = (*cmd)->next;
		return (TRUE);
	}
	return (FALSE);
}

char	**convert_env(t_minishell *mini)
{
	t_list	*current;
	char	**envtab;
	int		i;

	current = mini->env;
	i = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	envtab = ft_calloc(i + 1, sizeof(char *));
	current = mini->env;
	i = -1;
	while (current != NULL)
	{
		envtab[++i] = ft_strdup(current->content);
		current = current->next;
	}
	envtab[++i] = NULL;
	return (envtab);
}
