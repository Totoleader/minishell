/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:50:29 by macote            #+#    #+#             */
/*   Updated: 2023/06/19 11:06:10 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <libc.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

#define TEXT 1
#define REDIR_IN 2
#define REDIR_OUT 3
#define REDIR_OUT_DELIM 4
#define REDIR_OUT_APPEND 5
#define PIPE 6
#define LAST_COMMAND 7
#define VAR_ENV 8

#define NO_QUOTE 0
#define SINGLE_QUOTE 1
#define DOUBLE_QUOTE 2

// typedef struct s_minishell_input
// {
// 	char *command;
// 	t_token *tokens;
// 	char *flag;
// }				t_input;

typedef struct s_minishell_token
{
	char	*command;
	char	**args;
	char	*flag;
}				t_input;

typedef struct s_minishell
{
	t_list	*env;
	char	cwd[PATH_MAX];
}				t_minishell;

typedef struct s_token
{
	char *arg;
	int type;
	// int interpret_meta;
	// t_token *left_child;
	// t_token *right_child;
}				t_token;

//commands
char	*ft_getenv(t_minishell *mini, const char *varname);
void 	execute_command(t_input command, t_minishell *mini);
void	echo_(t_input command);
void	exit_(void);
void	env_(t_minishell *mini);
void	export_(t_minishell *mini, t_input command);
void	unset_(t_minishell *mini, t_input command);
void	pwd_(t_minishell *mini);

//parsing
t_token	*parse_input(char *input);

#endif