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

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "alist.h"
# include "dstr.h"

typedef void	(*t_builtin)(t_alist *args, int, int, char **);

typedef struct s_cmd
{
	t_anode		node;
	char		*path;
	t_builtin	builtin;
	t_alist		args;
	char		*redir_in_name;
	char		*redir_out_name;
}	t_cmd;

typedef struct s_arg
{
	t_anode		node;
	t_dstr		string;
}	t_arg;

t_arg	*arg_init(size_t size);
t_cmd	*cmd_init(void);

int		parse_commands(t_alist *commands, char *input);
int		run_commands(t_alist *commands, char **env);
int		free_commands(t_alist *commands, int retval);

// builtin
void	builtin_echo(char **args, int in_fd, int out_fd, char **env);
void	builtin_cd(char **args, int in_fd, int out_fd, char **env);
void	builtin_pwd(char **args, int in_fd, int out_fd, char **env);
void	builtin_export(char **args, int in_fd, int out_fd, char **env);
void	builtin_unset(char **args, int in_fd, int out_fd, char **env);
void	builtin_env(char **args, int in_fd, int out_fd, char **env);
void	builtin_exit(char **args, int in_fd, int out_fd, char **env);

#endif
