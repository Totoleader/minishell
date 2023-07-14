/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:50:29 by macote            #+#    #+#             */
/*   Updated: 2023/07/07 13:21:54 by scloutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <term.h>
# include <termios.h>
# include <libc.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

#define READ 0
#define WRITE 1

#define IN 0
#define OUT 1

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

extern int	error_code;

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
	int		infile_fd;
	char *outfile;
	int		outfile_fd;
	struct s_commands	*next;
	struct s_command	*prev;
}				t_commands;

typedef struct s_count
{
	int i;
	int j;
	int k;
}				t_count;

typedef struct s_fds
{
	int is_not_first;
	int std_backup[2];
	int pipe_fd[2];
	int last_pipe;
}				t_fds;

//commands
void 	execute_command(t_commands *cmds, t_minishell *mini);
void	exec_cmd_master(t_commands *cmds, t_minishell *mini);
void	echo_(char **args);
void	exit_(t_commands *cmds, t_minishell *mini);
void	env_(t_minishell *mini);
void	export_(t_minishell *mini, t_commands *command);
void	unset_(t_minishell *mini, t_commands *command);
void	pwd_(t_minishell *mini);
void	cd_(t_commands *cmds, t_minishell *mini);
int		get_path(t_commands *cmd, t_minishell *mini);
void	here_doc(t_commands *cmd, t_minishell *mini);

//parsing
t_token		*parse_input(char *input, t_minishell *mini);
t_commands	*fill_cmd(t_token *tokens);
char *alloc_copy(char *str);
void trimmer(t_token *token);
void interpret_dollar_signs(t_token *token, t_minishell *mini);

//utils
char	*ft_getenv(t_minishell *mini, const char *varname);
void	ft_setenv(t_minishell *mini, const char *varname, const char *val);
t_list	*ft_getenv_node(t_minishell *mini, const char *varname);
int	get_path(t_commands *cmd, t_minishell *mini);
char	*join_path(char *dir, char *cmd_name);
void	ft_free_tab(char **tabl);
char	**split_env(t_minishell *mini);
void redir(t_minishell *mini, t_commands *cmd, int is_not_first, int *pipe_fd, int last_pipe);
void	dup2_(int fd, int std);
void reset_std_in_out(int *std_backup);
void	printf_err(char *format, char *var);
int	is_valididentifier(char *arg);

//free
void free_cmds(t_commands *cmds);
void free_mini(t_minishell *mini);
void free_all(t_commands *cmds, t_minishell *mini);

#endif