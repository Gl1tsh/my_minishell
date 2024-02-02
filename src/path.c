/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:11:31 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/29 14:48:49 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path(char const *s1, char const *s2)
{
	size_t	size;
	char	*dest;
	int		i;
	int		c;

	i = 0;
	c = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	dest = malloc(sizeof(char) * size);
	if (!dest)
		return (NULL);
	while (s1[i])
		dest[c++] = s1[i++];
	dest[c++] = '/';
	i = 0;
	while (s2[i])
		dest[c++] = s2[i++];
	dest[c] = '\0';
	return (dest);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}

#include <string.h>
#define ft_strcmp strcmp
t_builtin	get_builtin(char *name)
{
	if (ft_strcmp(name, "exit") == 0)
		return (builtin_exit);
	else if (ft_strcmp(name, "echo") == 0)
		return (builtin_echo);
	else if (ft_strcmp(name, "pwd") == 0)
		return (builtin_pwd);
	else if (ft_strcmp(name, "cd") == 0)
		return (builtin_cd);
	else if (ft_strcmp(name, "env") == 0)
		return (builtin_env);
	else if (ft_strcmp(name, "export") == 0)
		return (builtin_export);
	else if (ft_strcmp(name, "unset") == 0)
		return (builtin_unset);
	else
		return (NULL);
}

int	path_or_builtin(t_cmd *cmd, t_env *env)
{
	char	**paths;
	char	*complete_path;
	int		i;

	cmd->builtin = get_builtin(cmd->args->dynamic_str.bytes);
	if (cmd->builtin != NULL)
		return (0);
	if (ft_strchr(cmd->args->dynamic_str.bytes, '/') != NULL)
	{
		if (access(cmd->args->dynamic_str.bytes, R_OK | X_OK) != 0)
			return (126);
		cmd->path = ft_strdup(cmd->args->dynamic_str.bytes);
		return (0);
	}
	paths = ft_split(get_env_var(env, "PATH"), ':');
	i = 0;
	while (paths[i] != NULL)
	{
		complete_path = join_path(paths[i], cmd->args->dynamic_str.bytes);
		if (access(complete_path, R_OK | X_OK) == 0)
		{
			cmd->path = complete_path;
			free_array(paths);
			return (0);
		}
		free(complete_path);
		i++;
	}
	free_array(paths);
	return (127);
}
