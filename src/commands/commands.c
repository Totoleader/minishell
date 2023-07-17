/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:30:29 by macote            #+#    #+#             */
/*   Updated: 2023/07/17 14:52:49 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//deals with commands that don't need to be forked/execve (builtins)
int	execute_builtin(t_commands *cmds, t_minishell *mini)
{
	if (!cmds->args || !cmds->args[0])
		return (TRUE);
	if (!ft_strncmp(cmds->args[0], "exit", 5))
		return (exit_(cmds, mini), TRUE);
	else if (!ft_strncmp(cmds->args[0], "echo", 5))
		return (echo_(&cmds->args[1]), TRUE);
	else if (!ft_strncmp(cmds->args[0], "env", 3))
		return (env_(mini), TRUE);
	else if (!ft_strncmp(cmds->args[0], "export", 6))
		return (export_(mini, cmds), TRUE);
	else if (!ft_strncmp(cmds->args[0], "unset", 5))
		return (unset_(mini, cmds), TRUE);
	else if (!ft_strncmp(cmds->args[0], "pwd", 3))
		return (pwd_(mini), TRUE);
	else if (!ft_strncmp(cmds->args[0], "cd", 2))
		return (cd_(cmds, mini), TRUE);
	return (FALSE);
}

//deals with commands that need to be forked/execve
void	*execve_command(t_commands *cmds, t_minishell *mini, int *std_backup,
		int *pipe_fd)
{
	int		pid;
	char	**env_;

	if (!get_path(cmds, mini))
		return (cmd_not_found(cmds->args[0]), NULL);
	pid = fork();
	if (pid == 0)
	{
		if (cmds->next)
			close(pipe_fd[READ]);
		env_ = convert_env(mini);
		close(std_backup[OUT]);
		close(std_backup[IN]);
		execve(cmds->args[0], cmds->args, env_);
		exit(EXIT_FAILURE);
	}
	waitpid(0, &g_error_code, 0);
	g_error_code = WEXITSTATUS(g_error_code);
	return (NULL);
}

//main function that deals with commands
void	exec_cmd_master(t_commands *cmds, t_minishell *mini)
{
	t_commands	*current;
	int			is_not_first;
	int			pipe_fd[2];
	int			last_pipe;

	if (!init_vars(&current, cmds, &is_not_first))
		return ;
	while (current)
	{
		if (check_file(&current))
			continue ;
		if (current->next)
			pipe(pipe_fd);
		if (redir_in(mini, current, is_not_first, last_pipe) == 1)
			break ;
		redir_out(current, pipe_fd);
		if (!execute_builtin(current, mini))
			execve_command(current, mini, mini->std_bak, pipe_fd);
		if (current->next)
			last_pipe = pipe_fd[READ];
		prep_next_cmd(&current, mini->std_bak, &is_not_first);
	}
	close_std_backups(mini->std_bak);
}
