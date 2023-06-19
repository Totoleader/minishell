/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scloutie <scloutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:50:29 by macote            #+#    #+#             */
/*   Updated: 2023/06/19 10:45:44 by scloutie         ###   ########.fr       */
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

typedef struct minishell_input
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


char	*ft_getenv(t_minishell *mini, const char *varname);

//commands
void 	execute_command(t_input command, t_minishell *mini);
void	echo_(t_input command);
void	exit_(void);
void	env_(t_minishell *mini);
void	export_(t_minishell *mini, t_input command);
void	unset_(t_minishell *mini, t_input command);
void	pwd_(t_minishell *mini);

//parsing
t_input parse_input(char *input);

#endif