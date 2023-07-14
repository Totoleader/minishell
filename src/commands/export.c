/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:43:48 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/14 11:32:57 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Gets an allocated copy of the data before '='
 **/
static char	*get_varname(char *arg)
{
	char	*out;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	out = malloc(sizeof(char) * (i + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		out[i] = arg[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

static void	add_var(t_minishell *mini, char *arg)
{
	char	*content;
	char	*var;

	if (!ft_strchr(arg, '='))
	{
		if (ft_getenv(mini, arg))
			return ;
		else
			ft_setenv(mini, arg, "");
	}
	else
	{
		var = get_varname(arg);
		if (!var)
			return ;
		content = ft_strchr(arg, '=') + 1;
		if (!content && !ft_getenv(mini, var))
			ft_setenv(mini, var, "");
		else if (*content)
			ft_setenv(mini, var, content);
		free(var);
	}
}

void	print_declare(t_minishell *mini)
{
	t_list	*lst;
	int		i;

	lst = mini->env;
	while (lst)
	{
		write(1, "declare -x ", 11);
		i = 0;
		while (lst->content[i])
		{
			write(1, &lst->content[i], 1);
			if (lst->content[i] == '=')
				write(1, "\"", 1);
			i++;
		}
		write(1, "\"\n", 2);
		lst = lst->next;
	}
}

void	export_(t_minishell *mini, t_commands *command)
{
	int		i;
	char	*varname;

	error_code = 0;
	i = 0;
	if (command->args[1] == NULL)
		print_declare(mini);
	else
	{
		while (command->args[++i] != NULL)
		{
			varname = get_varname(command->args[i]);
			if (!varname)
				continue ;
			if (!is_valididentifier(varname))
				printf_err("minishell: export: \'$\': Invalid identifier\n",
					varname);
			else
				add_var(mini, command->args[i]);
			free(varname);
		}
	}
}
