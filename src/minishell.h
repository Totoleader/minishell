/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:50:29 by macote            #+#    #+#             */
/*   Updated: 2023/06/22 12:38:28 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include <termios.h>
# include <curses.h>
# include <stdio.h>
# include <libc.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

#define READ 0
#define WRITE 1

#define TEXT 1
#define REDIR_IN 2
#define REDIR_OUT 3
#define REDIR_IN_DELIM 4
#define REDIR_OUT_APPEND 5
#define PIPE 6
#define LAST_COMMAND 7
#define COMMAND 9

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
	int interpret_meta;
}				t_token;

typedef struct s_commands
{
	int type_in;
	int	type_out;
	char **args;
	char *infile;
	int	infile_fd;
	char *outfile;
	int	outfile_fd;
	struct s_commands *next;
}				t_commands;

typedef struct s_count
{
	int i;
	int j;
	int k;
}				t_count;

//commands
void 	execute_command(t_commands *cmds, t_minishell *mini);
void	exec_cmd_master(t_commands *cmds, t_minishell *mini);
void	echo_(char **args);
void	exit_(void);
void	env_(t_minishell *mini);
void	export_(t_minishell *mini, t_input command);
void	unset_(t_minishell *mini, t_input command);
void	pwd_(t_minishell *mini);
void	cd_(t_commands *cmds, t_minishell *mini);

//parsing
t_token		*parse_input(char *input, t_minishell *mini);
t_commands	*fill_cmd(t_token *tokens);
char *alloc_copy(char *str);
void trimmer(t_token *token);
void interpret_dollar_signs(t_token *token, t_minishell *mini);

//utils
char	*ft_getenv(t_minishell *mini, const char *varname);
t_list	*ft_getenv_node(t_minishell *mini, const char *varname);

#endif