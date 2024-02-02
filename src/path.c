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
	int		i;

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
			exit_status = get_path(cmds, env);
			if (exit_status != 0)
			{
				cmds->path = NULL;
				return (exit_status);
			}
		}
		cmds = cmds->next;
	}
	return (0);
}
