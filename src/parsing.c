/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:47:19 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/26 14:21:03 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define VARNAME_CHARSET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\
0123456789_"
#define WHITESPACE_CHARSET " \t\n\v\f\r"

t_arg	*allocate_arg(t_arg *prev_arg)
{
	t_arg	*arg;

	arg = ft_calloc(1, sizeof(t_arg));
	if (prev_arg != NULL)
		prev_arg->next = arg;
	dstr_allocate(&arg->dynamic_str, 16);
	return (arg);
}

t_cmd	*allocate_cmd(t_cmd *prev_cmd)
{
	t_cmd *cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (prev_cmd != NULL)
		prev_cmd->next = cmd;
	cmd->args = allocate_arg(NULL);
	return (cmd);
}

char	*parse_dollar(t_arg *arg, char *input)
{
	char	*var_name_start;
	char	*var_name;
	char	*var_value;

	fprintf(stderr, "parse_dollar: enter [%s]\n", input);
	var_name_start = input;
	while (ft_strchr(VARNAME_CHARSET, *input))
		input++;

	fprintf(stderr, "parse_dollar: varname end [%s]\n", input);
	var_name = ft_strndup(var_name_start, input - var_name_start);
	var_value = getenv(var_name);
	fprintf(stderr, "parse_dollar: varname [%s] varvalue [%s]\n", var_name, var_value);
	if (var_value != NULL)
		dstr_append(&arg->dynamic_str, var_value, ft_strlen(var_value));
	free(var_name);
	fprintf(stderr, "parse_dollar: leaving\n");
	return (input);
}

char *parse_argument(t_arg *arg, char *input)
{
	if (*input == '"')
	{
		input++;
		while (*input != '"')
		{
			if (*input == '$')
				input = parse_dollar(arg, input + 1);
			else
				dstr_append(&arg->dynamic_str, input++, 1);
		}
		return (input + 1);
	}
	else if (*input == '\'')
	{
		input++;
		while (*input != '\'')
			dstr_append(&arg->dynamic_str, input++, 1);
		return (input + 1);
	}
	else
	{
		dstr_append(&arg->dynamic_str, input, 1);
		return (input + 1);
	}
}

//t_arg	*link_and_prepare_arg(t_arg *arg,)

int	parse_commands(t_cmd **head, char *input, char **env)
{
	t_cmd	*cmd;
	t_arg	*arg;

	cmd = allocate_cmd(NULL);
	*head = cmd;
	arg = cmd->args;

	while (*input)
	{
		fprintf(stderr, "parse_commands: *input [%c]\n", *input);
		if (*input == '|')
		{
			cmd = allocate_cmd(cmd);
			arg = cmd->args;
			input++;
			while (ft_strchr(WHITESPACE_CHARSET, *input))
				input++;
		}
		else if (ft_strchr(WHITESPACE_CHARSET, *input))
		{
			fprintf(stderr, "parse_commands: found space: arg: %s\n", arg->dynamic_str.bytes);
			while (ft_strchr(WHITESPACE_CHARSET, *input))
				input++;
			if (*input != '|')
				arg = allocate_arg(arg);
		}
		else
			input = parse_argument(arg, input);
	}
	return (0);
}
