/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:41 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/26 15:00:26 by nagiorgi         ###   ########.fr       */
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
		free(cmds->path);
		cmds = cmds->next;
	}
}

void	free_commands(t_cmd *cmds)
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
		next_cmd = cmds->next;
		free(cmds);
		cmds = next_cmd;
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
		{
			free(prompt);
			break ;
		}
		clean_input = ft_strtrim(input, WHITESPACE_CHARSET);
		if (*clean_input != '\0')
		{
			add_history(input);
			parse_commands(&cmds, clean_input, env);
			//run_commands(cmds, env);
			print_commands(cmds);
			free_commands(cmds);
		}
		free(prompt);
		free(input);
		free(clean_input);
	}
	return (0);
}
