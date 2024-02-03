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

int	free_commands(t_cmd *cmds, int exit_status, t_env *env)
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
	return (set_exit_status(exit_status, env));
}

int	launch_commands(char *input, t_env *env)
{
	int		exit_status;
	t_cmd	*cmds;

	exit_status = parse_commands(&cmds, input, env);
	if (exit_status != 0)
		return (free_commands(cmds, exit_status, env));
	//print_commands(cmds);
	exit_status = process_heredoc(cmds);
	if (exit_status != 0)
		return (free_commands(cmds, exit_status, env));
	exit_status = which_commands(cmds, env);
	if (exit_status != 0)
		return (free_commands(cmds, exit_status, env));
	exit_status = run_commands(cmds, env);
	return (free_commands(cmds, exit_status, env));
}

void	repl(t_env *env)
{
	char	*input;
	char	*prompt;
	char	*clean_input;
	int		exit_requested;

	prompt = NULL;
	exit_requested = 0;
	while (!exit_requested)
	{
		free(prompt);
		prompt = ft_strjoin(get_env_var(env, "PWD"), " > ");
		input = readline(prompt);
		if (input == NULL)
			break ;
		clean_input = ft_strtrim(input, WHITESPACE_CHARSET);
		if (clean_input != NULL && *clean_input != '\0')
		{
			add_history(input);
			if (launch_commands(clean_input, env) < 0)
				exit_requested = 1;
		}
		free(input);
		free(clean_input);
	}
	free(prompt);
}

int	main(int argc, char **argv, char **org_env)
{
	t_env	env;
	int		exit_status;

	(void)argc;
	(void)argv;
	env = dup_env(org_env);
	signal(SIGINT, parsing_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	repl(&env);
	exit_status = ft_atoi(get_env_var(&env, "?"));
	if (exit_status < 0)
		exit_status = 0;
	free_array(env);
	return (exit_status);
}
