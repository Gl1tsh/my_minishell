/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:11:31 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/10 09:06:05 by nagiorgi         ###   ########.fr       */
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

int	get_path(t_cmd *cmd, t_env *env)
{
	char	**paths;
	char	*env_path;
	int		i;

	env_path = get_env_var(env, "PATH");
	if (env_path == NULL)
		return (127);
	paths = ft_split(env_path, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		cmd->path = join_path(paths[i], cmd->args->dynamic_str.bytes);
		if (access(cmd->path, R_OK | X_OK) == 0)
		{
			free_array(paths);
			return (0);
		}
		free(cmd->path);
		i++;
	}
	free_array(paths);
	cmd->path = NULL;
	return (127);
}

int	which_commands(t_cmd *cmds, t_env *env)
{
	int	exit_status;

	while (cmds != NULL)
	{
		cmds->builtin = get_builtin(cmds->args->dynamic_str.bytes);
		if (cmds->builtin == NULL)
		{
			if (ft_strchr(cmds->args->dynamic_str.bytes, '/') != NULL)
			{
				if (access(cmds->args->dynamic_str.bytes, R_OK | X_OK) != 0)
					return (perror_return("command not found", 126));
				cmds->path = ft_strdup(cmds->args->dynamic_str.bytes);
			}
			else
			{
				exit_status = get_path(cmds, env);
				if (exit_status != 0)
					return (perror_return("command not found", exit_status));
			}
		}
		cmds = cmds->next;
	}
	return (0);
}
