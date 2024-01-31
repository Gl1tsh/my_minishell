/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:41 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/29 18:10:24 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>

void	parsing_signal_handler(int sig_num)
{
	(void)sig_num;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void print_commands(t_cmd *cmds)
{
	t_arg	*arg;

	while (cmds != NULL)
	{
		fprintf(stderr, "cmd: args %p\n", cmds->args);
		fprintf(stderr, "  dirin:  [%s]\n", cmds->dirin);
		fprintf(stderr, "  dirout: [%s]\n", cmds->dirout);
		arg = cmds->args;
		while (arg != NULL)
		{
			fprintf(stderr, "  arg: %p [%s]\n", arg->dynamic_str.bytes, arg->dynamic_str.bytes);
			arg = arg->next;
		}
		cmds = cmds->next;
	}
}

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
		free(cmds->dirin);
		free(cmds->dirout);
		next_cmd = cmds->next;
		free(cmds);
		cmds = next_cmd;
	}
	return (exit_status);
}

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
	exit_status = which_commands(cmds);
	if (exit_status != 0)
		return (free_commands(cmds, exit_status));
	exit_status = run_commands(cmds, env);
	return (free_commands(cmds, exit_status));
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	*prompt;
	char	*clean_input;

	(void)argc;
	(void)argv;
	signal(SIGINT, parsing_signal_handler);
	signal(SIGQUIT, SIG_IGN);
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
