/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:52:13 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/07 15:05:43 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <fcntl.h>

/* 
 * process_heredoc: Traite une redirection de type heredoc.
 * - Crée un fichier temporaire.
 * - Ouvre le fichier en mode écriture.
 * - Lit les lignes de l'entrée standard jusqu'à la fin du heredoc.
 * - Écrit chaque ligne dans le fichier temporaire.
 * - Renvoie 1 si une erreur se produit, sinon 0.
 */

int	process_heredoc(t_cmd *cmds)
{
	char	*line;
	char	*tmp_file_name;
	int		tmp_fd;

	tmp_file_name = "bonjour_tmp_file";
	if (cmds->dirin != NULL && cmds->dirin_mode == DIRIN_MODE_HEREDOC)
	{
		tmp_fd = open(tmp_file_name, O_TRUNC | O_WRONLY | O_CREAT, 0777);
		while (1)
		{
			line = readline("heredoc> ");
			if (line == NULL)
				return (1);
			if (ft_strcmp(line, cmds->dirin) == 0)
				break ;
			write(tmp_fd, line, ft_strlen(line));
			write(tmp_fd, "\n", 1);
			free(line);
		}
		close(tmp_fd);
		cmds->dirin = tmp_file_name;
	}
	cmds = cmds->next;
	while (cmds != NULL)
	{
		if (cmds->dirin != NULL && cmds->dirin_mode == DIRIN_MODE_HEREDOC)
			return (1);
		cmds = cmds->next;
	}
	return (0);
}
