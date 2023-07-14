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
	static t_minishell	*mini;
	static char			*cwd;

	if (!mini)
	{
		mini = malloc(sizeof(t_minishell));
		if (!mini)
			exit(1);
		ft_memset(mini, 0, sizeof(t_minishell));
		ft_memset(mini->cwd, 0, PATH_MAX);
		inherit_envp(mini, envp);
		cwd = ft_getenv(mini, "PWD");
		if (cwd)
			ft_strlcpy(mini->cwd, cwd, PATH_MAX);
		getcwd(mini->cwd, PATH_MAX);
	}
	return (mini);
}

void minishell(t_minishell *mini)
{
	t_token *tokens;
	char *input;
	t_commands *cmds;
	
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



int main(int argc, char **argv, char **envp)
{
	t_minishell			*mini;

	(void)argc;
	(void)argv;

	mini = init_minishell(envp);
	printf("\033[31mWelcome to minishell :)\n\n\033[0m");
	minishell(mini);
	// rl_clear_history();
	return (0);
}
