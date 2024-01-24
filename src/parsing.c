/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:10:53 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/23 17:23:15 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define STRIPPED_QUOTE  0x16    // using ASCII SYN
#define EXPAND_VAR      0x1A    // using ASCII SUB

#define VARNAME_CHARSET "ABCDEFGHIJKLMNOPQRSTUVWXYZ\
abcdefghijklmnopqrstuvwxyz0123456789_"

void	expand_retval(t_dstr *string_buffer)
{
	dstr_append(string_buffer, "987", 3);
}

void	expand_var(t_dstr *string_buffer, char *name_start, char *name_end)
{
	char	*name;
	char	*value;

	name = ft_substr(name_start, 0, name_end - name_start);
	value = getenv(name);
	if (value != NULL)
		dstr_append(string_buffer, value, ft_strlen(value));
	free(name);
}

void	copy_with_processing(t_dstr *string_buffer, char *src, char *end)
{
	char	*varname;

	while (src < end)
		if (*src == STRIPPED_QUOTE)
			src++;
		else if (*src == EXPAND_VAR)
		{
			src++;
			if (*src == '?')
			{
				expand_retval(string_buffer);
				src++;
			}
			else if (ft_strchr(VARNAME_CHARSET, *src))
			{
				varname = src;
				while (ft_strchr(VARNAME_CHARSET, *src))
					src++;
				expand_var(string_buffer, varname, src);
			}
			else
				dstr_append(string_buffer, src++, 1);
		}
		else
			dstr_append(string_buffer, src++, 1);
}

void	copy_part_to_args(t_cmd *cmd, char *begin, char *end)
{
	t_arg	*arg;

	arg = arg_init((end - begin) + 1);
	copy_with_processing(&arg->string, begin, end);
	alist_add_tail(&cmd->args, (t_anode *)arg);
}

char	*handle_special_chars(char *str)
{
	if (*str == '$')
		*str = EXPAND_VAR;
	else if (*str == '"')
	{
		*str = STRIPPED_QUOTE;
		while (*str != '"' && *(str + 1))
		{
			if (*str == '$')
				*str = EXPAND_VAR;
			str++;
		}
		*str = STRIPPED_QUOTE;
	}
	else if (*str == '\'')
	{
		*str = STRIPPED_QUOTE;
		while (*str != '\'' && *(str + 1))
			str++;
		*str = STRIPPED_QUOTE;
	}
	return (str);
}

int	parse_commands(t_alist *commands, char *str)
{
	int		previous_char_is_separator; // rename to `in_spaces` or `in_sep` (to lower the sline width)
	char	*part_begining;		// ?rename? to `part` (to lower the sline width)
	t_cmd	*cmd;

	/* factor out this idiom:
		if (!previous_char_is_separator)
			copy_part_to_args(cmd, part_begining, str);
		previous_char_is_separator = 1;
	   to:
		in_sep = add_args_after_sep(cmd, part, str, in_sep);
	*/

	cmd = cmd_init();

	previous_char_is_separator = 1;
	while (*str)
	{
		if (*str == '|')
		{
			if (!previous_char_is_separator)
				copy_part_to_args(cmd, part_begining, str);
			previous_char_is_separator = 1;

			alist_add_tail(commands, (t_anode *)cmd);
			cmd = cmd_init();
		}
		else if (*str == '>' || *str == '<')
		{
			if (!previous_char_is_separator)
				copy_part_to_args(cmd, part_begining, str);
			previous_char_is_separator = 1;

			if (*str == *(str + 1))
			{
				copy_part_to_args(cmd, str, str + 2);
				str++;
			}
			else
				copy_part_to_args(cmd, str, str + 1);
		}
		else if (*str == ' ' || *str == '\t')
		{
			if (!previous_char_is_separator)
				copy_part_to_args(cmd, part_begining, str);
			previous_char_is_separator = 1;
		}
		else
		{
			if (previous_char_is_separator)
				part_begining = str;
			previous_char_is_separator = 0;
			str = handle_special_chars(str);
		}
		++str;
	}
	if (!previous_char_is_separator)
		copy_part_to_args(cmd, part_begining, str);

	alist_add_tail(commands, (t_anode *)cmd);
	return 0;
}
