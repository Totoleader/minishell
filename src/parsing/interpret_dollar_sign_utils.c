/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_dollar_sign_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:10:56 by macote            #+#    #+#             */
/*   Updated: 2023/07/24 10:19:01 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_delimiter(t_token *token, t_count *c)
{
	if (token->arg[c->i] == '$' && token->arg[c->i + 1] && token->arg[c->i
			+ 1] != '$' && token->arg[c->i + 1] != '\'' && token->arg[c->i
			+ 1] != '\"' && token->arg[c->i + 1] != ' ')
		return (TRUE);
	return (FALSE);
}

// interpret_dollar_signs() helper
void	dollar_sign_helper(char *args, t_list **vars, int *i)
{
	static int	within_dq = FALSE;

	if (args[(*i)] == '\"')
		within_dq = !within_dq;
	if (args[(*i)] == '\'' && ft_strchr(&args[(*i) + 1], '\'') && !within_dq)
	{
		(*i)++;
		while (args[(*i)] != '\'')
			(*i)++;
	}
	if (args[(*i)] == '$' && args[(*i) + 1] && args[(*i) + 1] != '\''
		&& args[(*i) + 1] != '\"' && args[(*i) + 1] != ' ' && args[(*i)
			+ 1] != '$')
	{
		if (args[(*i) + 1] == '{' && ft_strchr(&args[(*i) + 1], '}'))
		{
			*ft_strchr(&args[(*i) + 1], '}') = ' ';
			(*i)++;
		}
		ft_lstadd_back(vars, ft_lstnew(get_var_env_name(&args[(*i) + 1])));
	}
	(*i)++;
}

static void	increment_counters(int *i, int *count)
{
	(*i)++;
	(*count)++;
}

// count_size_with_vars() helper
void	count_size_helper(char *args, int *i, int *count)
{
	if (args[(*i)] == '\'' && ft_strchr(&args[(*i) + 1], '\''))
	{
		(*count)++;
		(*i)++;
		while (args[(*i)] != '\'')
			increment_counters(i, count);
	}
	else if (args[(*i)] == '$' && args[(*i) + 1] && args[(*i) + 1] != ' '
		&& args[(*i) + 1] != '\'' && args[(*i) + 1] != '\"' && args[(*i)
			+ 1] != '$')
	{
		(*i)++;
		while (args[(*i)] && args[(*i)] != ' ' && args[(*i)] != '\''
			&& args[(*i)] != '\"' && args[(*i)] != '$' && args[(*i)] != '?')
			(*i)++;
		if (args[(*i)] == '?')
			(*i)++;
	}
	else if (args[(*i)])
		increment_counters(i, count);
}
