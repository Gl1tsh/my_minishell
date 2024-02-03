/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:47:19 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/26 14:26:05 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (prev_cmd != NULL)
		prev_cmd->next = cmd;
	cmd->args = allocate_arg(NULL);
	return (cmd);
}

char	*skip_whitespace(char *input)
{
	while (*input && ft_strchr(WHITESPACE_CHARSET, *input))
		input++;
	return (input);
}
