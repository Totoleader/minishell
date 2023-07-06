/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 08:52:54 by macote            #+#    #+#             */
/*   Updated: 2023/07/06 13:48:59 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_code;

char	*ft_getenv(t_minishell *mini, const char *varname)
{
	t_list	*lst;
	size_t	varlen;
	char	*fullname;

	if (!mini || !mini->env || !varname)
		return (NULL);
	lst = mini->env;
	fullname = ft_strjoin(varname, "=");
	varlen = ft_strlen(fullname);
	while (lst)
	{
		if (ft_strnstr(lst->content, fullname, varlen))
		{
			free(fullname);
			return (&lst->content[varlen]);
		}
		lst = lst->next;
	}
	free(fullname);
	return (NULL);
}

void	ft_setenv(t_minishell *mini, const char *varname, const char *val)
{
	t_list	*varnode;
	int		add;
	char	*temp;
	char	*fullvar;

	add = 1;
	varnode = ft_getenv_node(mini, varname);
	if (varnode)
	{
		add = 0;
		free(varnode->content);
	}
	temp = ft_strjoin(varname, "=");
	fullvar = ft_strjoin(temp, val);
	free(temp);
	if (add)
		ft_lstadd_back(&mini->env, ft_lstnew(fullvar));
	else
		varnode->content = fullvar;
}

t_list	*ft_getenv_node(t_minishell *mini, const char *varname)
{
	t_list	*lst;
	char	*to_find;

	lst = mini->env;
	to_find = ft_strjoin(varname, "=");
	if (!to_find)
		return (NULL);
	while (lst)
	{
		if (ft_strnstr(lst->content, to_find, ft_strlen(to_find)))
		{
			free(to_find);
			return (lst);
		}
		lst = lst->next;
	}
	free(to_find);
	return (NULL);
}

void	inherit_envp(t_minishell *mini, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(envp[i++])));
}

t_minishell	*init_minishell(char **envp)
{
	t_minishell	*mini;
	char		*cwd;

	mini = malloc(sizeof(t_minishell));
	if (!mini)
		exit(1);
	mini->env = NULL;
	ft_memset(mini->cwd, 0, PATH_MAX);
	inherit_envp(mini, envp);
	cwd = ft_getenv(mini, "PWD");
	if (cwd)
		ft_strlcpy(mini->cwd, cwd, PATH_MAX);
	getcwd(mini->cwd, PATH_MAX);
	return (mini);
}


void free_cmds(t_commands *cmds)
{
	t_commands *current;
	t_commands *to_free;
	int i;

	i = 0;
	current = cmds;
	while (current)
	{
		to_free = current;
		if (current->args)
		{
			while (current->args[i])
				free(current->args[i++]);
			free(current->args);
		}
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		current = current->next;
		free(to_free);
	}
}

void free_mini(t_minishell *mini)
{
	ft_lstclear(&mini->env);
	free(mini);
}

// void free_all(t_commands *cmds, t_minishell *mini)
// {
// 	free_cmds(cmds);
// 	free(mini);
// }

void minishell(t_minishell *mini)
{
	t_token *tokens;
	char *input;
	t_commands *cmds;
	
	while (TRUE)
	{
		input = readline("minishell $ ");
		if (!input)
			exit(0);
		if (input && *input)
			add_history(input);

		tokens = parse_input(input, mini);
		cmds = fill_cmd(tokens);

		exec_cmd_master(cmds, mini);
	}
	free_mini(mini);
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		error_code = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishell			*mini;
	struct sigaction	sa;
	struct termios		term;

	(void)argc;
	(void)argv;

	// Term stuff
	tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;	// Turns off all echo ctrl characters (like ^C and ^\)
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

	// Signal stuff
	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);

	mini = init_minishell(envp);
	printf("\033[31mWelcome to minishell :)\n\n\033[0m");
	minishell(mini);
	rl_clear_history();
	return (0);
}
