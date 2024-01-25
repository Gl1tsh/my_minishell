/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:41 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/24 18:41:34 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>

void print_commands(t_cmd *cmds)
{
	t_arg	*arg;

	while (cmds != NULL)
	{
		fprintf(stderr, "\ncmd:\n");
		fprintf(stderr, "  args: %p \n", cmds->args);
		arg = cmds->args;
		while (arg != NULL)
		{
			fprintf(stderr, "  arg: %p [%s]\n", arg, arg ? arg->dynamic_str.bytes : "");
			arg = arg->next;
		}
		cmds = cmds->next;
	}
}

int free_commands(t_cmd *cmd, int retval)
{
	t_arg	*arg;
	t_arg	*next_arg;
	t_cmd	*next_cmd;

	if (retval)
		printf("Error %d\n", retval);

	while (cmd != NULL)
	{
		arg = cmd->args;
		while (arg != NULL)
		{
			next_arg = arg->next;
			dstr_free(&arg->dynamic_str);
			free(arg);
			arg = next_arg;
		}
		next_cmd = cmd->next;
		free(cmd);
		cmd = next_cmd;
	}

	return retval;
}

int	process(char *input, char **env)
{
	t_cmd	*cmds;
	int		retval;

	retval = parse_commands(&cmds, input, env);
	if (retval)
		return free_commands(cmds, retval);

	//retval = run_commands(cmds, env);
	print_commands(cmds);
	return free_commands(cmds, retval);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	*trimmed_input;
	char	*prompt;

	(void)argc;
	(void)argv;
	while (1)
	{
		prompt = ft_strjoin(getenv("PWD"), " > ");
		input = readline(prompt);
		free(prompt);
		if (!input)
			break ;
		trimmed_input = ft_strtrim(input, " \t");
		if (*trimmed_input)
		{
			add_history(trimmed_input);
			process(trimmed_input, env);
		}
		free(trimmed_input);
		free(input);
	}
	return (0);
}
