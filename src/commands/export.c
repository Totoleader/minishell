/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:43:48 by scloutie          #+#    #+#             */
/*   Updated: 2023/07/03 11:51:44 by macote           ###   ########.fr       */
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

static int	is_valididentifier(char c)
{
	return (c == '_' || ft_isalpha(c));
}

void	export_(t_minishell *mini, t_commands *command)
{
	int		i;
  error_code = 0;
	i = 1;
	if (command->args[i] == NULL)
		env_(mini);
	else
	{
		while (command->args[i] != NULL)
		{
			if (!is_valididentifier(command->args[i][0]))
				ft_putstr_fd("minishell: export: Invalid identifier\n", 2);
			else
				add_var(mini, command->args[i]);
			i++;
		}
	}
}
