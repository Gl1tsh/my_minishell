/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:41 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/07 15:09:07 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
 * Index:
 * 1. print_commands: Affiche les commandes stockées dans une structure t_cmd.
 * 2. free_commands: Libère la mémoire allouée pour une liste de commandes.
 * 3. which_commands: Détermine si chaque commande est une commande intégrée ou un chemin d'accès.
 * 4. launch_commands: Traite une chaîne d'entrée et exécute les commandes correspondantes.
 * 5. main: Point d'entrée du programme.
 */

#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>

/* 
 * print_commands: Affiche les commandes stockées dans une structure t_cmd.
 * - Parcourt la liste de commandes.
 * - Pour chaque commande, affiche les arguments et les redirections.
 */

void print_commands(t_cmd *cmds)
{
	t_arg	*arg;

	while (cmds != NULL)
	{
		fprintf(stderr, "\ncmd : args %p \n", cmds->args);
		arg = cmds->args;
		while (arg != NULL)
		{
			fprintf(stderr, "  arg : %p \n", arg);
			fprintf(stderr, "  arg : [%s]\n", arg->dynamic_str.bytes);
			arg = arg->next;
		}
		fprintf(stderr, "dirin : [%s]\n", cmds->dirin);
		fprintf(stderr, "dirout : [%s]\n", cmds->dirout);
		fprintf(stderr, "dirin_mode : [%d]\n", cmds->dirin_mode);
		fprintf(stderr, "dirout_mode : [%d]\n", cmds->dirout_mode);
		fprintf(stderr, "path : [%s]\n", cmds->path);
		cmds = cmds->next;
	}
}

/* 
 * free_commands: Libère la mémoire allouée pour une liste de commandes.
 * - Parcourt la liste de commandes.
 * - Pour chaque commande, libère la mémoire allouée pour
 * 		les arguments et le chemin.
 * - Renvoie le statut de sortie donné.
 */

int	free_commands(t_cmd *cmds, int exit_status)
{
	t_arg	*arg;
	t_arg	*next_arg;
	t_cmd	*next_cmd;

	while (cmds != NULL)
	{
		arg = cmds->args;
		while (arg != NULL)
		{
			dstr_free(&arg->dynamic_str);
			next_arg = arg->next;
			free(arg);
			arg = next_arg;
		}
		free(cmds->path);
		next_cmd = cmds->next;
		free(cmds);
		cmds = next_cmd;
	}
	return (exit_status);
}

/* 
 * which_commands: Détermine si chaque commande est une commande intégrée
 		ou un chemin d'accès.
 * - Parcourt la liste de commandes.
 * - Pour chaque commande, appelle path_or_builtin.
 * - Si path_or_builtin renvoie une erreur, renvoie le statut de sortie.
 * - Sinon, renvoie 0.
 */

int	which_commands(t_cmd *cmds)
{
	int	exit_status;

	while (cmds != NULL)
	{
		exit_status = path_or_builtin(cmds);
		if (exit_status != 0)
			return (exit_status);
		cmds = cmds->next;
	}
	return (0);
}

/* 
 * launch_commands: Traite une chaîne d'entrée et exécute
 		les commandes correspondantes.
 * - Appelle parse_commands pour traiter la chaîne d'entrée.
 * - Si parse_commands renvoie une erreur, libère les commandes et
 * 		renvoie le statut de sortie.
 * - Appelle process_heredoc pour traiter les redirections de type heredoc.
 * - Si process_heredoc renvoie une erreur, libère les commandes et
 * 		renvoie le statut de sortie.
 * - Appelle which_commands pour déterminer si chaque commande est
 * 		une commande intégrée ou un chemin d'accès.
 * - Si which_commands renvoie une erreur, libère les commandes et
 * 		renvoie le statut de sortie.
 * - Appelle run_commands pour exécuter les commandes.
 * - Libère les commandes et renvoie le statut de sortie.
 */

int	launch_commands(char *input, char **env)
{
	int	exit_status;
	t_cmd	*cmds;

	exit_status = parse_commands(&cmds, input, env);
	if (exit_status != 0)
		return (free_commands(cmds, exit_status));
	print_commands(cmds);
	exit_status = process_heredoc(cmds);
	if (exit_status != 0)
		return (free_commands(cmds, exit_status));
	print_commands(cmds);
	exit_status = which_commands(cmds);
	if (exit_status != 0)
		return (free_commands(cmds, exit_status));
	exit_status = run_commands(cmds, env);
	return (free_commands(cmds, exit_status));
}

/* 
 * main: Point d'entrée du programme.
 * - Lit une ligne de l'entrée standard.
 * - Si la ligne est vide, libère la mémoire allouée et continue la boucle.
 * - Sinon, ajoute la ligne à l'historique et appelle launch_commands.
 * - Libère la mémoire allouée pour la ligne et continue la boucle.
 * - Renvoie 0 à la fin.
 */

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	*prompt;
	char	*clean_input;

	(void)argc;
	(void)argv;
	while (1)
	{
		prompt = ft_strjoin(getenv("PWD"), " > ");
		input = readline(prompt);
		if (input == NULL)
		{
			free(prompt);
			break ;
		}
		clean_input = ft_strtrim(input, WHITESPACE_CHARSET);
		if (*clean_input != '\0')
		{
			add_history(input);
			launch_commands(clean_input, env);
		}
		free(prompt);
		free(input);
		free(clean_input);
	}
	return (0);
}
