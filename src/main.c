/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:41 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/26 14:32:41 by nagiorgi         ###   ########.fr       */
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
		fprintf(stderr, "cmd : args %p \n", cmds->args);
		arg = cmds->args;
		while (arg != NULL)
		{
			fprintf(stderr, "arg : %p \n", arg);
			fprintf(stderr, "arg : [%s]\n", arg->dynamic_str.bytes);
			arg = arg->next;
		}
		cmds = cmds->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	*prompt;
	t_cmd	*cmds;
	char	*clean_input;

	(void)argc;
	(void)argv;
	while (1)
	{
		prompt = ft_strjoin(getenv("PWD"), " > ");
		input = readline(prompt);
		if (input == NULL)
			break ;
		clean_input = ft_strtrim(input, WHITESPACE_CHARSET);
		if (*clean_input != '\0')
		{
			add_history(input);
			parse_commands(&cmds, clean_input, env);
			//run_commands(cmds, env);
			print_commands(cmds);
		}
		free(input);
		free(clean_input);
	}
	return (0);
}
