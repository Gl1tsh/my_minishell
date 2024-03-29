/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:57:44 by tomuller          #+#    #+#             */
/*   Updated: 2024/02/10 09:08:04 by nagiorgi         ###   ########.fr       */
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
# define VARNAME_CHARSET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\
0123456789_"

typedef char	**t_env;

// pointed fonction for builtin
typedef int		(*t_builtin)(char **, t_env *);

typedef struct s_arg
{
	t_dstr			dynamic_str;
	struct s_arg	*next;
}	t_arg;

// struct for one command
typedef struct s_cmd
{
	char			*path;
	t_arg			*args;
	t_builtin		builtin;
	char			*dirin;
	char			*dirout;
	int				dirin_mode;
	int				dirout_mode;
	struct s_cmd	*next;
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
int			which_commands(t_cmd *commands, t_env *env);
void		print_commands(t_cmd *commands);

// other
char		*join_path(char const *s1, char const *s2);
void		parsing_signal_handler(int sig_num);
void		free_array(char **array);
int			perror_return(char *message, int exit_status);
int			redirect(int oldfd, int newfd);
int			set_exit_status(int exit_status, t_env *env);
char		**dup_env(char **env);
int			is_valid_var_name(char *var);
int			exec_pipeline(t_cmd *cmds, int in_fd, int out_fd, t_env *env);
void		safe_close(int fd);

// builtin
int			builtin_echo(char **args, t_env *env);
int			builtin_cd(char **args, t_env *env);
int			builtin_pwd(char **args, t_env *env);
int			builtin_export(char **args, t_env *env);
int			builtin_unset(char **args, t_env *env);
int			builtin_env(char **args, t_env *env);
int			builtin_exit(char **args, t_env *env);

#endif
