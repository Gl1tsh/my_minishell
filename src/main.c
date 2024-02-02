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

int	set_exit_status(int exit_status, t_env *env)
{
	char	*value;
	char	*var;

	value = ft_itoa(exit_status);
	var = ft_strjoin("?=", value);
	update_env_var(env, var);
	free(var);
	free(value);
	return (exit_status);
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

int	which_commands(t_cmd *cmds, t_env *env)
{
	int	exit_status;

	while (cmds != NULL)
	{
		exit_status = path_or_builtin(cmds, env);
		if (exit_status != 0)
			return (exit_status);
		cmds = cmds->next;
	}
	return (0);
}

int	launch_commands(char *input, t_env *env)
{
	int		exit_status;
	t_cmd	*cmds;

	exit_status = parse_commands(&cmds, input, env);
	if (exit_status != 0)
		return (free_commands(cmds, exit_status, env));
	print_commands(cmds);
	exit_status = process_heredoc(cmds);
	if (exit_status != 0)
		return (free_commands(cmds, exit_status, env));
	exit_status = which_commands(cmds, env);
	if (exit_status != 0)
		return (free_commands(cmds, exit_status, env));
	exit_status = run_commands(cmds, env);
	return (free_commands(cmds, exit_status, env));
}

char	**dup_env(char **env)
{
	int		size;
	int		i;
	char	**new_env;

	size = get_env_size(env);
	new_env = ft_calloc(sizeof(char *), size + 2);
	i = 0;
	while (i < size)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[size] = ft_strdup("?=0");
	return (new_env);
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

	(void)argc;
	(void)argv;
	env = dup_env(org_env);
	signal(SIGINT, parsing_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	repl(&env);
	free_array(env);
	return (0);
}
