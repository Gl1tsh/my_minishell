/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:57:44 by tomuller          #+#    #+#             */
/*   Updated: 2024/01/23 17:19:46 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd	s_cmd;

typedef void			(*t_builtin)(char **, int, int, char **);

typedef struct s_cmd
{
	char				*path;
	char				*cmd;
	char				**args;
	t_builtin			builtin;
	char				*dirin;
	char				*dirout;
	s_cmd				*next;
}						t_cmd;

typedef struct s_builtin_map
{
	char				*name;
	t_builtin			func;
}						t_builtin_map;

// CLEAN.C
void					free_cmd_list(t_cmd *cmd_lst);
void					free_tab(char **tab);

// PATH.C
void					programm_path(t_cmd *lst);
bool					is_programm(t_cmd *lst);
char					*get_path(t_cmd *list);
void					check_path(t_cmd *list);

// PARSING.C
void					add_redirection(char **cmd_split, int *j, t_cmd *node);
t_cmd					*init_cmd(char **split);
void					parsing(const char *input, char **env);

// LST_UTILS.C
void					update_cmd_with_builtin(t_cmd *node);
t_cmd					*init_node_variables(t_cmd *node);
t_cmd					*create_new_cmd_node(char **cmd_split);
t_cmd					*cmd_lastlst(t_cmd *lst);
void					cmd_lstadd_back(t_cmd **lst, t_cmd *new);

// UTILS.C
void					print_command_details(t_cmd *cmd, int count);
void					print_cmd(t_cmd *cmd_lst);
void					init_map(t_builtin_map *builtin_map);
void    				print_args(char **args);

// builtin
void					builtin_echo(char **args, int in_fd, int out_fd, char **env);
void					builtin_cd(char **args, int in_fd, int out_fd, char **env);
void					builtin_pwd(char **args, int in_fd, int out_fd, char **env);
void					builtin_export(char **args, int in_fd, int out_fd, char **env);
void					builtin_unset(char **args, int in_fd, int out_fd, char **env);
void					builtin_env(char **args, int in_fd, int out_fd, char **env);
void					builtin_exit(char **args, int in_fd, int out_fd, char **env);

void    run_commands(t_cmd *commands, char **env);

#endif