/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:47:19 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/26 14:26:05 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include <fcntl.h>
#include <sys/errno.h>

char	*parse_dollar(t_arg *arg, char *input, t_env *env)
{
	char	*var_name_start;
	char	*var_name;
	char	*var_value;

	if (*input == '?')
	{
		var_value = get_env_var(env, "?");
		if (var_value != NULL)
			dstr_append(&arg->dynamic_str, var_value, ft_strlen(var_value));
		return (input + 1);
	}
	var_name_start = input;
	while (*input && ft_strchr(VARNAME_CHARSET, *input))
		input++;
	var_name = ft_strndup(var_name_start, input - var_name_start);
	var_value = get_env_var(env, var_name);
	if (var_value != NULL)
		dstr_append(&arg->dynamic_str, var_value, ft_strlen(var_value));
	free(var_name);
	return (input);
}

char	*parse_argument(t_arg *arg, char *input, t_env *env)
{
	if (*input == '"')
	{
		input++;
		while (*input != '"')
		{
			if (*input == '$')
				input = parse_dollar(arg, input + 1, env);
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

char	*parse_redir(t_cmd *cmd, char *input, t_env *env)
{
	t_arg	fake_arg;
	char	redir_char;

	cmd->dirout_mode = O_CREAT | O_TRUNC | O_WRONLY;
	redir_char = *input++;
	if (*input == redir_char)
	{
		input++;
		if (redir_char == '>')
			cmd->dirout_mode = O_CREAT | O_APPEND | O_WRONLY;
		else if (redir_char == '<')
			cmd->dirin_mode = DIRIN_MODE_HEREDOC;
	}
	dstr_allocate(&fake_arg.dynamic_str, 16);
	input = skip_whitespace(input);
	while (*input && !ft_strchr(WHITESPACE_CHARSET "|<>", *input))
		input = parse_argument(&fake_arg, input, env);
	input = skip_whitespace(input);
	if (redir_char == '>')
		cmd->dirout = ft_strdup(fake_arg.dynamic_str.bytes);
	else if (redir_char == '<')
		cmd->dirin = ft_strdup(fake_arg.dynamic_str.bytes);
	dstr_free(&fake_arg.dynamic_str);
	return (input);
}

int	internal_parse_commands(t_cmd *cmd, char *input, t_env *env)
{
	t_arg	*arg;

	arg = cmd->args;
	while (*input)
	{
		if (*input == '|')
		{
			cmd = allocate_cmd(cmd);
			arg = cmd->args;
			input = skip_whitespace(input + 1);
		}
		else if (*input == '$')
			input = parse_dollar(arg, input + 1, env);
		else if (*input == '<' || *input == '>')
			input = parse_redir(cmd, input, env);
		else if (ft_strchr(WHITESPACE_CHARSET, *input))
		{
			input = skip_whitespace(input);
			if (*input != '|' && *input != '>' && *input != '<')
				arg = allocate_arg(arg);
		}
		else
			input = parse_argument(arg, input, env);
	}
	return (0);
}

int	parse_commands(t_cmd **head, char *input, t_env *env)
{
	int	len;

	len = ft_strlen(input);
	if (input[0] == '|' || input[len - 1] == '|')
	{
		*head = NULL;
		errno = EINVAL;
		return (perror_return("parsing pipe", 1));
	}
	*head = allocate_cmd(NULL);
	return (internal_parse_commands(*head, input, env));
}
