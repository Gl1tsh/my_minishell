/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:10:53 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/23 17:23:15 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_free(void *param)
{
	t_arg	*arg;

	arg = (t_arg *)param;
	alist_remove(param);
	free(arg->string.bytes);
	free(arg);
}

void	cmd_free(void *param)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)param;
	alist_remove(param);
	alist_each(&cmd->args, &arg_free);
	free(cmd);
}

t_arg	*arg_init(size_t size)
{
	t_arg	*arg;

	arg = ft_calloc(1, sizeof(t_arg));
	dstr_allocate(&arg->string, size);
	return (arg);
}

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	alist_new_list(&cmd->args);
	return (cmd);
}

int	free_commands(t_alist *commands, int retval)
{
	alist_each(commands, &cmd_free);
	return (retval);
}
