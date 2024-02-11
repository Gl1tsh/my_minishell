/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:14:42 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/11 14:39:52 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_commands(t_cmd *cmds)
{
	t_arg	*arg;

	while (cmds != NULL)
	{
		fprintf(stderr, "cmd: args %p\n", cmds->args);
		fprintf(stderr, "  dirin:  [%s]\n", cmds->dirin);
		fprintf(stderr, "  dirout: [%s]\n", cmds->dirout);
		arg = cmds->args;
		while (arg != NULL)
		{
			fprintf(stderr, "  arg: [%s]\n", arg->dynamic_str.bytes);
			arg = arg->next;
		}
		cmds = cmds->next;
	}
}

int	set_exit_status(int exit_status, t_env *env)
{
	char	*value;
	char	*var;
	int		status;

	status = exit_status;
	if (exit_status < 0)
		status = -exit_status;
	value = ft_itoa(status);
	var = ft_strjoin("?=", value);
	update_env_var(env, var);
	free(var);
	free(value);
	return (exit_status);
}

char	**dup_env(char **env)
{
	int		size;
	int		i;
	char	**new_env;

	size = get_env_size(env);
	new_env = ft_calloc(sizeof(char *), size + 2);
	i = 0;
	while (i < size)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[size] = ft_strdup("?=0");
	return (new_env);
}

// Returns true if the content of var before '=' or EOS is a valid variable name
int	is_valid_var_name(char *var)
{
	char	*eos;

	eos = ft_strchr(var, '=');
	if (eos == NULL)
		eos = var + ft_strlen(var);
	while (var < eos)
	{
		if (ft_strchr(VARNAME_CHARSET, *var) == NULL)
			return (0);
		var++;
	}
	return (1);
}

int	perror_return(char *message, int exit_status)
{
	perror(message);
	return (exit_status);
}
