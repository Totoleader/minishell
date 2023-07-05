/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_dollar_sign.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:43:13 by macote            #+#    #+#             */
/*   Updated: 2023/07/05 12:08:40 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// replace_vars() helper
void replace_with_var_content(t_token *token, char *new_content, t_count *c, t_list *current)
{
	c->i++;
	while (token->arg[c->i] && token->arg[c->i] != ' ' && token->arg[c->i] != '\''
		&& token->arg[c->i] != '\"' && token->arg[c->i] != '$')
		c->i++;
	c->k = 0;
	while (current->content && current->content[c->k])
		new_content[c->j++] = current->content[c->k++];
	current = current->next;
}

void replace_vars(t_token *token, t_list *vars, int count)
{
	t_list *current;
	char *new_content;
	t_count *c;

	c = malloc(sizeof(t_count));
	current = vars;
	token->arg = token->arg;
	c->i = 0;
	c->j = 0;
	new_content = ft_calloc(sizeof(char), count + 1);
	while (c->j < count && token->arg[c->i])
	{
		if (token->arg[c->i] == '$' && token->arg[c->i + 1] && token->arg[c->i + 1] != '$'
			&& token->arg[c->i + 1] != '\'' && token->arg[c->i + 1] != '\"' && token->arg[c->i + 1] != ' ')
			{
				replace_with_var_content(token, new_content, c, current);
				current = current->next;
			}
		else
			new_content[c->j++] = token->arg[c->i++];
	}
	free(c);
	ft_lstclear(&vars);
	free(token->arg);
	token->arg = new_content;
}

// count_size_with_vars() helper
void count_size_helper(char *args, int *i, int *count)
{
	if (args[(*i)] == '\'' && ft_strchr(&args[(*i) + 1], '\''))
	{
		(*count)++;
		(*i)++;
		while (args[(*i)] != '\'')
		{
			(*count)++;
			(*i)++;
		}
	}
	else if (args[(*i)] == '$' && args[(*i) + 1] && args[(*i) + 1] != ' ' && args[(*i) + 1] != '\'' && args[(*i) + 1] != '\"' && args[(*i) + 1] != '$')
	{
		(*i)++;
		while (args[(*i)] && args[(*i)] != ' ' && args[(*i)] != '\'' && args[(*i)] != '\"' && args[(*i)] != '$')
			(*i)++;
	}
	else if (args[(*i)])
	{
		(*i)++;
		(*count)++;
	}
}

void count_size_with_vars(t_token *token, t_list *vars)
{
	int i;
	int count;
	char *args;
	t_list *current;

	args = token->arg;
	count = 0;
	i = 0;
	while (token->type == TEXT && args[i])
	{
		count_size_helper(args, &i, &count);
	}
	current = vars;
	while (current)
	{
		count += ft_strlen(current->content);
		current = current->next;
	}
	replace_vars(token, vars, count);
}

char *get_var_env_name(char *str)
{
	int i;
	int count;
	char *var_name;

	count = 1;
	while (str[count] && str[count] != ' ' && str[count] != '$' && str[count] != '\'' && str[count] != '\"')
		count++;
	var_name = ft_calloc(sizeof(char), count + 1);
	i = 0;
	while (i < count)
	{
		var_name[i] = str[i];
		i++;
	}
	return (var_name);
}

// interpret_dollar_signs() helper
void interpret_dollar_sign_helper(char *args, t_list **vars, int *i)
{
	if (args[(*i)] == '\'' && ft_strchr(&args[(*i) + 1], '\''))
		{
			(*i)++;
			while (args[(*i)] != '\'')
				(*i)++;
		}
		
		if (args[(*i)] == '$' && args[(*i) + 1] && args[(*i) + 1] != '\'' && args[(*i) + 1] != '\"' && args[(*i) + 1] != ' ' && args[(*i) + 1] != '$')
		{
			ft_lstadd_back(vars, ft_lstnew(get_var_env_name(&args[(*i) + 1])));
		}
		(*i)++;
}

void interpret_dollar_signs(t_token *token, t_minishell *mini)
{
	t_list *vars;
	t_list *current;
	char *args;
	int i;
	
	if (token->type != TEXT || !ft_strchr(token->arg, '$'))
		return ;
	vars = NULL;
	i = 0;
	args = token->arg;
	while (token->type == TEXT && args[i])
	{
		interpret_dollar_sign_helper(args, &vars, &i);
	}
	current = vars;
	while (current)
	{
		if (!ft_strncmp(current->content, "?", 2))
			args = ft_itoa(error_code);
		else
			args = ft_getenv(mini, current->content);
		free(current->content);
		current->content = args;
		current = current->next;
	}
	if (vars)
		count_size_with_vars(token, vars);
}
