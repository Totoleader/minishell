/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:38:53 by macote            #+#    #+#             */
/*   Updated: 2023/07/19 12:05:54 by scloutie         ###   ########.fr       */
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

//inits the mini struct that contains env vars
t_minishell	*init_minishell(char **envp)
{
	static t_minishell	*mini;
	static char			*cwd;

	if (!mini)
	{
		mini = ft_calloc(1, sizeof(t_minishell));
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
