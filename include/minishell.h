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

typedef char **t_env;

// pointed fonction for builtin
typedef int	(*t_builtin)(char **, t_env *);

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
int			get_env_size(char **env);
char		*get_env_var(t_env *env, char *var_name);
void		update_env_var(t_env *env, char *var);
void		remove_env_var(t_env *env, char *var_name);

// commands
int			parse_commands(t_cmd **head, char *input, t_env *env);
int			run_commands(t_cmd *commands, t_env *env);
int			process_heredoc(t_cmd *commands);

// other
int			path_or_builtin(t_cmd *cmd, t_env *env);
char		*join_path(char const *s1, char const *s2);
void		parsing_signal_handler(int sig_num);
void		free_array(char **array);

// builtin
int			builtin_echo(char **args, t_env *env);
int			builtin_cd(char **args, t_env *env);
int			builtin_pwd(char **args, t_env *env);
int			builtin_export(char **args, t_env *env);
int			builtin_unset(char **args, t_env *env);
int			builtin_env(char **args, t_env *env);
int			builtin_exit(char **args, t_env *env);

#endif