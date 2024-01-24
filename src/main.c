/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:41 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/23 17:22:42 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	process(char *input, char **env)
{
	t_alist	commands;
	int		retval;

	alist_new_list(&commands);
	retval = parse_commands(&commands, input);
	if (retval)
		return (free_commands(&commands, retval));

	/*
	retval = extract_redirections(&commands);
	if (retval)
		return (free_commands(&commands, retval));
	retval = process_heredoc(&commands);
	if (retval)
		return (free_commands(&commands, retval));
	retval = setup_path_or_builtin(&commands);
	if (retval)
		return (free_commands(&commands, retval));
	*/

	retval = run_commands(&commands, env);
	return (free_commands(&commands, retval));
}

void	set_retval(int retval)
{
	(void)retval;
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	*prompt;

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
			set_retval(process(input, env));
		}
		free(input);
		free(prompt);
	}
	return (0);
}
