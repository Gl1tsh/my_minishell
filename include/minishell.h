/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:57:44 by tomuller          #+#    #+#             */
/*   Updated: 2024/01/26 12:57:09 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "dstr.h"

// pointed fonction for builtin
typedef void	(*t_builtin)(char **, int, int, char **);

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
	struct s_cmd	*next; // chained list of cmds
}	t_cmd;

int			parse_commands(t_cmd **head, char *input, char **env);
int			run_commands(t_cmd *commands, char **env);

// builtin
void		builtin_echo(char **args, int in_fd, int out_fd, char **env);
void		builtin_cd(char **args, int in_fd, int out_fd, char **env);
void		builtin_pwd(char **args, int in_fd, int out_fd, char **env);
void		builtin_export(char **args, int in_fd, int out_fd, char **env);
void		builtin_unset(char **args, int in_fd, int out_fd, char **env);
void		builtin_env(char **args, int in_fd, int out_fd, char **env);
void		builtin_exit(char **args, int in_fd, int out_fd, char **env);

#endif