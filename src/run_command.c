/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:10:53 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/07 15:00:16 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Fonctions dans run_command.c :
 * - convert_args         : Convertit args en tableau.
 * - perror_return        : Affiche erreur.
 * - safe_close           : Ferme descripteur > 2.
 * - cmd_signal_handler   : Gère signaux.
 * - redirect             : Redirige descripteur.
 * - exec_builtin         : Exécute commande intégrée.
 * - exec_cmd             : Exécute commande non intégrée.
 * - setup_pipe           : Configure pipe.
 * - exec_pipeline        : Exécute commandes avec pipes.
 * - setup_redirections   : Configure redirections.
 * - run_commands         : Exécute commandes avec redirections et pipes.
 */

#include "minishell.h"
#include <fcntl.h>

/* 
 * convert_args: Transforme une liste chaînée d'arguments en tableau.
 * - Parcourt la liste pour compter le nombre d'éléments.
 * - Alloue de la mémoire pour le tableau avec malloc.
 * - Remplit le tableau avec les arguments de la liste.
 * - Ajoute un NULL à la fin pour indiquer la fin.
 * - Renvoie le tableau d'arguments.
 */

char	**convert_args(t_arg *args)
{
	char	**args_array;
	t_arg	*args_head;
	int 	i;

	i = 0;
	args_head = args;
	while (args != NULL)
	{
		i++;
		args = args->next;
	}
	args_array = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (args_head != NULL)
	{
		args_array[i] = args_head->dynamic_str.bytes;
		args_head = args_head->next;
		i++;
	}
	args_array[i] = NULL;
	return (args_array);
}

/* 
 * convert_args: Transforme une liste chaînée d'arguments en tableau.
 * - Parcourt la liste pour compter le nombre d'éléments.
 * - Alloue de la mémoire pour le tableau avec malloc.
 * - Remplit le tableau avec les arguments de la liste.
 * - Ajoute un NULL à la fin pour indiquer la fin.
 * - Renvoie le tableau d'arguments.
 */

int	perror_return(char *message, int exit_status)
{
	perror(message);
	return (exit_status);
}

/* 
 * convert_args: Transforme une liste chaînée d'arguments en tableau.
 * - Parcourt la liste pour compter le nombre d'éléments.
 * - Alloue de la mémoire pour le tableau avec malloc.
 * - Remplit le tableau avec les arguments de la liste.
 * - Ajoute un NULL à la fin pour indiquer la fin.
 * - Renvoie le tableau d'arguments.
 */

void	safe_close(int fd)
{
	if (fd >= 2)
		close(fd);
}

/* 
 * cmd_signal_handler: Gère les signaux pendant l'exécution d'une commande.
 * - Ne fait rien pour le moment.
 */

void	cmd_signal_handler(int sig_num)
{
	(void)sig_num;
	//rien mettre
}

/* 
 * redirect: Redirige un descripteur de fichier vers un autre.
 * - Utilise dup2 pour rediriger oldfd vers newfd.
 * - Ferme oldfd si la redirection a réussi.
 * - Renvoie 0 si la redirection a réussi, sinon renvoie
 * 		le résultat de perror_return.
 */

int redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) != -1)
			safe_close(oldfd);
		else
			return (perror_return("redirect", 1));
	}
	return (0);
}

/* 
 * exec_builtin: Exécute une commande intégrée.
 * - Duplique les descripteurs standard d'entrée et de sortie.
 * - Redirige in_fd vers l'entrée standard et fd[1] vers la sortie standard.
 * - Exécute la commande intégrée.
 * - Restaure les descripteurs standard d'entrée et de sortie.
 * - Renvoie le statut de sortie de la commande intégrée.
 */

int	exec_builtin(t_cmd *cmds, int in_fd, int *fd, char **env)
{
	int exit_status;
	int	tmp_fd[2];

	tmp_fd[0] = dup(STDIN_FILENO);
	tmp_fd[1] = dup(STDOUT_FILENO);
	if (redirect(in_fd, STDIN_FILENO) != 0)
		return (1);
	if (redirect(fd[1], STDOUT_FILENO) != 0)
		return (1);
	exit_status = cmds->builtin(convert_args(cmds->args), env);
	if (redirect(tmp_fd[0], STDIN_FILENO) != 0)
		return (1);
	if (redirect(tmp_fd[1], STDOUT_FILENO) != 0)
		return (1);
	return (exit_status);
}

/* 
 * exec_cmd: Exécute une commande non intégrée.
 * - Crée un nouveau processus avec fork.
 * - Redirige in_fd vers l'entrée standard et fd[1] vers la sortie standard
 * 		dans le processus fils.
 * - Exécute la commande non intégrée dans le processus fils.
 * - Renvoie l'ID du processus fils dans le processus parent.
 */

int	exec_cmd(t_cmd *cmds, int in_fd, int *fd, char **env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return perror_return("exec_cmd", 1);
	if (pid == 0)
	{
		safe_close(fd[0]);
		if (redirect(in_fd, STDIN_FILENO) != 0)
			exit(127);
		if (redirect(fd[1], STDOUT_FILENO) != 0)
			exit(127);
		execve(cmds->path, convert_args(cmds->args), env);
		perror("exec");
		exit(127);
	}
	safe_close(fd[1]);
	safe_close(in_fd);
	return (pid);
}

/* 
 * setup_pipe: Configure un pipe entre deux commandes.
 * - Si cmds->next est NULL, configure fd[1] pour écrire dans out_fd.
 * - Sinon, crée un nouveau pipe avec la fonction pipe.
 * - Renvoie 0 si la configuration a réussi, sinon renvoie
 * 		le résultat de perror_return.
 */

int	setup_pipe(t_cmd *cmds, int out_fd, int *fd)
{
	if (cmds->next == NULL)
	{
		fd[0] = -1;
		fd[1] = out_fd;
		return (0);
	}
	if (pipe(fd) == -1)
		return (perror_return("setup_pipe", 1));
	return (0);
}

/* 
 * exec_pipeline: Exécute une série de commandes connectées par des pipes.
 * - Configure un pipe avec setup_pipe.
 * - Exécute la commande courante avec exec_builtin ou exec_cmd.
 * - Si cmds->next n'est pas NULL, exécute récursivement le 
 * 		reste de la pipeline.
 * - Attend que le processus fils se termine avec waitpid.
 * - Renvoie 0.
 */

int	exec_pipeline(t_cmd *cmds, int in_fd, int out_fd, char **env)
{
	int fd[2];
	int	pid;
	int	status;

	fprintf(stderr, "exec_pipeline: running\n");
	if (setup_pipe(cmds, out_fd, fd) != 0)
		return (1);
	if (cmds->builtin != NULL)
	{
		exec_builtin(cmds, in_fd, fd, env);
		pid = 0;
	}
	else
		pid = exec_cmd(cmds, in_fd, fd, env);
	if (cmds->next != NULL)
		return (exec_pipeline(cmds->next, fd[0], out_fd, env));
	waitpid(pid, &status, 0);
	return 0;
}

/* 
 * setup_redirections: Configure les redirections pour les commandes.
 * - Si cmds->dirin n'est pas NULL, ouvre le fichier pour la lecture et 
 * 		duplique l'entrée standard.
 * - Si cmds->dirout n'est pas NULL, ouvre le fichier pour l'écriture et 
 * 		duplique la sortie standard.
 * - Renvoie 0.
 */

int	setup_redirections(t_cmd *cmds, int *fd)
{
	if (cmds->dirin != NULL)
	{
		fd[0] = open(cmds->dirin, O_RDONLY);
		if (cmds->dirin_mode == DIRIN_MODE_HEREDOC)
			unlink(cmds->dirin);
		fd[2] = dup(STDIN_FILENO);
	}
	while (cmds->next != NULL)
		cmds = cmds->next;
	if (cmds->dirout != NULL)
	{
		fd[1] = open(cmds->dirout, cmds->dirout_mode, 0777);
		fd[3] = dup(STDOUT_FILENO);
	}
	return (0);
}

/* 
 * run_commands: Exécute une série de commandes avec gestion 
 		des redirections et des pipes.
 * - Configure les redirections avec setup_redirections.
 * - Installe un gestionnaire de signaux avec signal.
 * - Exécute la pipeline de commandes avec exec_pipeline.
 * - Restaure les descripteurs standard d'entrée et de sortie si nécessaire.
 * - Renvoie le statut de sortie de exec_pipeline.
 */

int	run_commands(t_cmd *commands, char **env)
{
	int	fd[4];
	int	exit_status;

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	fd[2] = -1;
	fd[3] = -1;

	exit_status = setup_redirections(commands, fd);
	if (exit_status == 0)
	{
		signal(SIGINT, &cmd_signal_handler);
		signal(SIGQUIT, &cmd_signal_handler);
		// fprintf(stderr, "run_commands: before\n");
		exit_status = exec_pipeline(commands, fd[0], fd[1], env);
	}
	if (fd[2] > 0)
		redirect(fd[2], STDIN_FILENO);
	if (fd[3] > 0)
		redirect(fd[3], STDOUT_FILENO);
	return (exit_status);
}
