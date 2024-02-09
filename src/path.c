/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:11:31 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/09 10:52:41 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
 * Index:
 * 1. join_path: Concatène deux chaînes avec un '/' entre elles.
 * 2. free_array: Libère un tableau de chaînes.
 * 3. get_builtin: Renvoie une fonction intégrée correspondant au nom donné.
 * 4. path_or_builtin: Détermine si une commande est une commande intégrée ou un chemin d'accès.
 */

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

/* 
 * free_array: Libère un tableau de chaînes.
 * - Parcourt le tableau et libère chaque chaîne.
 * - Libère le tableau lui-même.
 */

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}

t_builtin	get_builtin(char *str)
{
	if (ft_strcmp(str, "cd") == 0)
		return (builtin_cd);
	else if (ft_strcmp(str, "echo") == 0)
		return (builtin_echo);
	else if (ft_strcmp(str, "env") == 0)
		return (builtin_env);
	else if (ft_strcmp(str, "exit") == 0)
		return (builtin_exit);
	else if (ft_strcmp(str, "pwd") == 0)
		return (builtin_pwd);
	// else if (ft_strcmp(str, "unset") == 0)
	// 	return (builtin_unset);
	// else if (ft_strcmp(str, "export") == 0)
	// 	return (builtin_export);
}

int	get_path(t_cmd *cmd, t_env *env)
{
	char	**paths;
	char	**env_path;
	int		i;

	env_path = get_env_path(env, "PATH");
	if (env_path == NULL)
		return (127);
	paths = ft_split(env_path, ":");
	i = 0;
	while (paths[i] != NULL)
	{
		cmd->path = join_path(paths[i], cmd->args->dynamic_str.bytes);
		if (acces(cmd->path, R_OK | W_OK) == 0)
		{
			free_array(cmd->path);
			return (0);
		}
		free(cmd->path);
		i++;
	}
	free_array(paths);
	cmd->path == NULL;
	return (127);
}

int	wich_commands(t_cmd *cmds, t_env *env)
{
	int	exit_status;

	while (cmds != NULL)
	{
		cmds->builtin = get_builtin(cmds->args->dynamic_str.bytes);
		if (cmds->args == NULL)
		{
			if (ft_strchr(cmds->args->dynamic_str.bytes, '/') != NULL)
			{
				if (access(cmds->args->dynamic_str.bytes, R_OK | W_OK) != 0)
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
