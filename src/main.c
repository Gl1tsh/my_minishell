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

	fprintf(stderr, "cmd : args %p \n", cmds->args);
	arg = cmds->args;
	while (arg != NULL)
	{
		fprintf(stderr, "arg : %p \n", arg);
		fprintf(stderr, "arg : [%s]\n", arg->dynamic_str.bytes);
		arg = arg->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	*prompt;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	while (1)
	{
		prompt = ft_strjoin(getenv("PWD"), " > ");
		input = readline(prompt);
		if (!input)
			break ;
		if (*input)
		{
			add_history(input);
			parse_commands(&cmds, input, env);
			//run_commands(cmds, env);
			print_commands(cmds);
		}
		free(input);
	}
	return (0);
}
