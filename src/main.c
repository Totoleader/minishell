/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 08:52:54 by macote            #+#    #+#             */
/*   Updated: 2023/06/20 14:17:44 by scloutie         ###   ########.fr       */
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

t_minishell	*init_minishell(void)
{
	t_minishell	*mini;

	mini = malloc(sizeof(t_minishell));
	if (!mini)
		exit(1);
	mini->env = NULL;
	ft_memset(mini->cwd, 0, PATH_MAX);
	return (mini);
}

void	inherit_envp(t_minishell *mini, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(envp[i++])));
}

void minishell(t_minishell *mini)
{
	t_token *tokens;
	char *input;

	while (TRUE)
	{
		input = readline("\033[31mminishell $ \033[0m");
		if (!input)
			exit(0);
		// input = ft_calloc(sizeof(char), 100);
		// ft_strlcpy(input, " <> >", 55);
		// ft_strlcpy(input, "", 55);
	
		tokens = parse_input(input);
		t_commands *cmds = fill_cmd(tokens);
		execute_command(cmds, mini);
		
	}
}


int main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;
	char		*cwd;

	(void)argc;
	(void)argv;

	mini = init_minishell();
	inherit_envp(mini, envp);
	cwd = ft_getenv(mini, "PWD");
	if (cwd)
		ft_strlcpy(mini->cwd, cwd, PATH_MAX);
	getcwd(mini->cwd, PATH_MAX);
	printf("\033[31mWelcome to minishell :)\n\n\033[0m");
	minishell(mini);
	return (0);
}
