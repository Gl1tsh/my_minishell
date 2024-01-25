/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:47:19 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/24 18:53:48 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define VARNAME_CHARSET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\
0123456789_"

t_arg	*allocate_arg(t_arg *current)
{
	t_arg	*arg;
	arg = ft_calloc(1, sizeof(t_arg));
	dstr_allocate(&arg->dynamic_str, 16);
	if (current)
		current->next = arg;
	return (arg);
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

char	*skip_spaces(char *input)
{
	while (*input == ' ' || *input == '\t')
		input++;
	return (input);
}

t_cmd	*allocate_cmd(t_cmd *current)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->args = allocate_arg(NULL);
	if (current)
		current->next = cmd;
	return (cmd);
}

int	internal_parse_commands(t_cmd *cmd, char *input, char **env)
{
	t_arg	*arg;

	arg = cmd->args;
	while (*input)
	{
		if (*input == '|')
		{
			input = skip_spaces(input + 1);
			if (*input == '|' || *input == '\0')
				return 1; //ERROR_ORPHANED_PIPE;

			cmd = allocate_cmd(cmd);
			arg = cmd->args;
		}
		else if (*input == ' ' || *input == '\t')
		{
			input = skip_spaces(input);
			if (*input != '|')
				arg = allocate_arg(arg);
		}
		else
			input = parse_argument(arg, input);
	}
	return (0);
}

int	parse_commands(t_cmd **head, char *input, char **env)
{
	if (*input == '|')
	{
		*head = NULL;
		return 1; //ERROR_ORPHANED_PIPE;
	}

	*head = allocate_cmd(NULL);
	return internal_parse_commands(*head, input, env);
}
