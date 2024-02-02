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
	int	size;

	size = 0;
	while (*env++)
		size++;
	return (size);
}

void	append_env_var(t_env *env, char *var)
{
	int		size;
	int		i;
	char	**new_env;
	char	**cur_env;

	cur_env = *env;
	size = get_env_size(cur_env);
	new_env = ft_calloc(sizeof(char *), size + 2);
	i = 0;
	while (i < size)
	{
		new_env[i] = cur_env[i];
		i++;
	}
	new_env[size] = ft_strdup(var);
	free(cur_env);
	*env = new_env;
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
	char	**cur_env;
	char	*equal;

	equal = ft_strchr(var, '=');
	if (equal == NULL)
		return ;
	cur_env = *env;
	while (*cur_env)
	{
		if (ft_strncmp(*cur_env, var, equal - var + 1) == 0)
		{
			free(*cur_env);
			*cur_env = ft_strdup(var);
			return ;
		}
		cur_env++;
	}
	append_env_var(env, var);
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
