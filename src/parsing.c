/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:47:19 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/24 17:31:21 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*allocate_arg(void)
{
	t_arg	*arg;
	arg = malloc(sizeof(t_arg));
	dstr_allocate(&arg->dynamic_str, 16);
	return (arg);
}

char *parse_argument(t_arg *arg, char *input)
{
	dstr_append(&arg->dynamic_str, input, 1);
	return (input + 1);
}

int	parse_commands(t_cmd **head, char *input, char **env)
{
	t_cmd	*cmd;
	t_arg	*arg;

	t_arg	*last_arg;
	t_arg	**next_arg_in_cmd;

	cmd = malloc(sizeof(t_cmd));
	next_arg_in_cmd = &cmd->args;
	arg = allocate_arg();

	while (*input)
	{
		if (*input == '|')
		{
			*head = cmd;
			return (0);
		}
		else if (*input == ' ' || *input == '\t')
		{
			*next_arg_in_cmd = arg;
			last_arg = arg;
			arg = allocate_arg();
			next_arg_in_cmd = &last_arg->next;
			while (*input == ' ' || *input == '\t')
				input++;
		}
		else
			input = parse_argument(arg, input);
	}
	return (0);
}
