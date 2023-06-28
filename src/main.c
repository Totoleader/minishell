/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 08:52:54 by macote            #+#    #+#             */
/*   Updated: 2023/06/26 13:34:22 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void minishell(t_minishell *mini)
{
	t_token *tokens;
	char *input;
	while (TRUE)
	{
		input = readline("minishell $ ");
		if (!input)
			exit(0);
		if (input && *input)
			add_history(input);
		// input = ft_calloc(sizeof(char), 100);
		// ft_strlcpy(input, " <> >", 55);
		// ft_strlcpy(input, "", 55);

		tokens = parse_input(input, mini);
		t_commands *cmds = fill_cmd(tokens);
		
		exec_cmd_master(cmds, mini);
		// free command structs and tokens
	}
}


int main(int argc, char **argv, char **envp)
{
	t_minishell		*mini;

	(void)argc;
	(void)argv;
	mini = init_minishell(envp);
	inherit_envp(mini, envp);
	cwd = ft_getenv(mini, "PWD");
	if (cwd)
		ft_strlcpy(mini->cwd, cwd, PATH_MAX);
	getcwd(mini->cwd, PATH_MAX);
	printf("\033[31mWelcome to minishell :)\n\n\033[0m");
	minishell(mini);
	return (0);
}
