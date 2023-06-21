/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 08:52:54 by macote            #+#    #+#             */
/*   Updated: 2023/06/21 13:11:39 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char    *ft_getenv(t_minishell *mini, const char *varname)
{
    t_list  *lst;
    size_t  varlen;
    char    *fullname;
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
		add_history(input);
		tokens = parse_input(input, mini);
		// execute_command(command, mini);
	}
	fill_cmd(tokens);
	
}

//fix '$'
int main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;
	char		*cwd;

	(void)argc;
	(void)argv;
	// char *cwd = malloc(100);
	// printf("%s\n", getcwd(cwd, 100));
	// chdir("/Users/scloutie");
	// printf("%s\n", getcwd(cwd, 100));


	// mini = init_minishell();
	// inherit_envp(mini, envp);
	// cwd = ft_getenv(mini, "PWD=");
	// if (cwd)
	// 	ft_strlcpy(mini->cwd, cwd, PATH_MAX);
	// printf("\033[31mWelcome to minishell :)\n\n\033[0m");
	// minishell(mini);
	mini = init_minishell();
	inherit_envp(mini, envp);
	cwd = ft_getenv(mini, "PWD");
	if (cwd)
		ft_strlcpy(mini->cwd, cwd, PATH_MAX);
	printf("\033[31mWelcome to minishell :)\n\n\033[0m");
	minishell(mini);
	return (0);
}
