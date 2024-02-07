/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:11:31 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/07 15:02:03 by nagiorgi         ###   ########.fr       */
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

/* 
 * run_commands: Exécute une série de commandes avec gestion des redirections et des pipes.
 * - Configure les redirections avec setup_redirections.
 * - Installe un gestionnaire de signaux avec signal.
 * - Exécute la pipeline de commandes avec exec_pipeline.
 * - Restaure les descripteurs standard d'entrée et de sortie si nécessaire.
 * - Renvoie le statut de sortie de exec_pipeline.
 */

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

/* 
 * get_builtin: Renvoie une fonction intégrée correspondant au nom donné.
 * - Pour l'instant, ne fait rien et renvoie NULL.
 */

t_builtin	get_builtin(char *name)
{
	(void)name;
	return NULL;
}

/* 
 * path_or_builtin: Détermine si une commande est une commande intégrée ou un chemin d'accès.
 * - Vérifie si la commande est une commande intégrée avec get_builtin.
 * - Si c'est le cas, stocke la fonction dans cmd->builtin et renvoie 0.
 * - Si la commande contient un '/', vérifie si c'est un chemin d'accès valide.
 * - Si c'est le cas, stocke le chemin dans cmd->path et renvoie 0.
 * - Sinon, parcourt les chemins dans la variable d'environnement PATH.
 * - Pour chaque chemin, concatène le chemin et la commande avec join_path.
 * - Vérifie si le chemin complet est un chemin d'accès valide.
 * - Si c'est le cas, stocke le chemin dans cmd->path, libère les chemins et renvoie 0.
 * - Si aucun chemin n'est valide, libère les chemins et renvoie 1.
 */

int	path_or_builtin(t_cmd *cmd)
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
			return (1);
		cmd->path = ft_strdup(cmd->args->dynamic_str.bytes);
		return (0);
	}
	paths = ft_split(getenv("PATH"), ':');
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
	return (1);
}
