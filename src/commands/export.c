/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:43:48 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/06 13:36:56 by scloutie         ###   ########.fr       */
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

	i = -1;
	while (arg[++i] != '=')
		;
	out = malloc(sizeof(char) * (i + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (arg[i] != '=')
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

static int	is_valididentifier(char *arg)
{
	int		is_valid_first;
	int		is_valid_string;
	int		i;

	if (!arg)
		return (0);
	is_valid_first = (arg[0] == '_' || ft_isalpha(arg[0]));
	if (!is_valid_first)
		return (0);
	is_valid_string = 1;
	i = 0;
	while (arg[i])
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i]))
			is_valid_string = 0;
		i++;
	}
	return (is_valid_string && is_valid_first);
}

void	export_(t_minishell *mini, t_commands *command)
{
	int		i;
	char	*varname;

	error_code = 0;
	i = 1;
	if (command->args[i] == NULL)
		env_(mini);
	else
	{
		while (command->args[i] != NULL)
		{
			varname = get_varname(command->args[i]);
			if (!varname)
			{
				i++;
				continue ;
			}
			if (!is_valididentifier(varname))
				ft_putstr_fd("minishell: export: Invalid identifier\n", 2);
			else
				add_var(mini, command->args[i]);
			free(varname);
			i++;
		}
	}
}
