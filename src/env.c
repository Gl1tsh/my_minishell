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
	new_env = malloc(sizeof(char *) * (size + additional_slot_count + 1));
	new_env[size] = NULL;
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
	return NULL;
}

t_env	*update_env_var(t_env *env, char *var_name, char *var_value)
{
	int		size;
	int		len;
	char	**new_env;
	char	**cur_env;
	char	*var;

	cur_env = *env;
	while (*cur_env)
	{
		len = ft_strlen(var_name);
		if (ft_strncmp(*cur_env, var_name, len) == 0 && *cur_env[len + 1] == '=')
		{
			fprintf(stderr, "update_env_var: found current var [%s]\n", *cur_env);
			return env;
		}
		cur_env++;
	}
	size = get_env_size(*env);
	new_env = copy_env(*env, 1);
	len = ft_strlen(var_name) + 1 + ft_strlen(var_value);
	var = ft_calloc(1, len + 1);
	ft_strlcat(var, var_name, len);
	ft_strlcat(var, "=", len);
	ft_strlcat(var, var_value, len);
	new_env[size] = var;
	*env = new_env;
}

void	remove_env_var(t_env *env, char *var_name)
{
	char	**cur_env;
	int		len;

	cur_env = *env;
	while (*cur_env)
	{
		len = ft_strlen(var_name);
		if (ft_strncmp(*cur_env, var_name, len) == 0 && *cur_env[len + 1] == '=')
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
