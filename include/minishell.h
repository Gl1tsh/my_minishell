/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:57:44 by tomuller          #+#    #+#             */
/*   Updated: 2024/01/29 18:02:42 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "dstr.h"

# define WHITESPACE_CHARSET " \t\n\v\f\r"

// pointed fonction for builtin
typedef int	(*t_builtin)(char **, char **);

typedef struct s_arg
{
	t_dstr			dynamic_str;
	struct s_arg	*next;
}	t_arg;

// struct for one command
typedef struct s_cmd
{
	char			*path; //real cmd path
	t_arg			*args; // all arguments from cmd line
	t_builtin		builtin; //pointer to builtin
	char			*dirin; // redirect in
	char			*dirout; // redirect out
	int				dirin_mode;
	int				dirout_mode;
	struct s_cmd	*next; // chained list of cmds
}	t_cmd;

# define DIRIN_MODE_HEREDOC 1

// env
typedef char **t_env;

char		**copy_env(char **env, int additional_slot_count);
char		*get_env_var(t_env *env, char *var_name);
t_env		*update_env_var(t_env *env, char *var_name, char *var_value);
void		remove_env_var(t_env *env, char *var_name);

int			parse_commands(t_cmd **head, char *input);
int			run_commands(t_cmd *commands, t_env *env);
int			process_heredoc(t_cmd *commands);

int			path_or_builtin(t_cmd *cmd);
char		*join_path(char const *s1, char const *s2);
void		parsing_signal_handler(int sig_num);

// builtin
int			builtin_echo(char **args, char **env);
int			builtin_cd(char **args, char **env);
int			builtin_pwd(char **args, char **env);
int			builtin_export(char **args, char **env);
int			builtin_unset(char **args, char **env);
int			builtin_env(char **args, char **env);
int			builtin_exit(char **args, char **env);

#endif