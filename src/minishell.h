/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:50:29 by macote            #+#    #+#             */
/*   Updated: 2023/06/18 14:17:06 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
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
	char *arg;
	int type;
	int interpret_meta;
	// t_token *left_child;
	// t_token *right_child;
}				t_token;

//commands
void execute_command(t_token *command);
void	echo_(t_token *command);
void	exit_(void);

//parsing
t_token	*parse_input(char *input);

#endif