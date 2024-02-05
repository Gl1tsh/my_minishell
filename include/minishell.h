/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:57:44 by tomuller          #+#    #+#             */
/*   Updated: 2024/02/05 16:26:38 by nagiorgi         ###   ########.fr       */
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
# define DIRIN_MODE_HEREDOC 1

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

int			parse_commands(t_cmd **head, char *input, char **env);
int			run_commands(t_cmd *commands, char **env);

int			path_or_builtin(t_cmd *cmd);
int			process_heredoc(t_cmd *cmds);

// builtin
int			builtin_echo(char **args, char **env);
int			builtin_cd(char **args, char **env);
int			builtin_pwd(char **args, char **env);
int			builtin_export(char **args, char **env);
int			builtin_unset(char **args, char **env);
int			builtin_env(char **args, char **env);
int			builtin_exit(char **args, char **env);

#endif