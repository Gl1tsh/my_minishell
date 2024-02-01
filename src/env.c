/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:11:31 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/29 14:48:49 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_size(char **env)
{
	int size;

	size = 0;
	while (*env++)
		size++;
	return (size);
}

char	**copy_env(char **env, int additional_slot_count)
{
	int 	size;
	int		i;
	char	**new_env;

	size = get_env_size(env);
	new_env = ft_calloc(sizeof(char *), size + additional_slot_count + 1);
	i = 0;
	while (i < size)
	{
		new_env[i] = env[i];
		i++;
	}
	return (new_env);
}

char	*get_env_var(t_env *env, char *var_name)
{
	int		len;
	char	**cur_env;

	len = ft_strlen(var_name);
	cur_env = *env;
	while (*cur_env)
	{
		if (ft_strncmp(*cur_env, var_name, len) == 0 && (*cur_env)[len] == '=')
			return ((*cur_env) + len + 1);
		cur_env++;
	}
	return (NULL);
}

void	update_env_var(t_env *env, char *var)
{
	int		size;
	char	**new_env;
	char	**cur_env;
	char	*equal;

	fprintf(stderr, "update_env_var: enter var [%s]\n", var);
	equal = ft_strchr(var, '=');
	if (equal == NULL)
		return ;
	cur_env = *env;
	fprintf(stderr, "update_env_var: loop [%s]\n", *cur_env);
	while (*cur_env)
	{
		if (ft_strncmp(*cur_env, var, equal - var + 1) == 0)
		{
			fprintf(stderr, "update_env_var: found current var [%s]\n", *cur_env);
			free(*cur_env);
			*cur_env = ft_strdup(var);
			return ;
		}
		cur_env++;
	}
	size = get_env_size(*env);
	new_env = copy_env(*env, 1);
	new_env[size] = ft_strdup(var);
	free_array(*env);
	*env = new_env;
}

void	remove_env_var(t_env *env, char *var_name)
{
	int		len;
	char	**cur_env;

	len = ft_strlen(var_name);
	cur_env = *env;
	while (*cur_env)
	{
		if (ft_strncmp(*cur_env, var_name, len) == 0 && (*cur_env)[len] == '=')
		{
			while (*cur_env)
			{
				*cur_env = *(cur_env + 1);
				cur_env++;
			}
			return ;
		}
		cur_env++;
	}
}
