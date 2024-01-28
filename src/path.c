/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:11:31 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/26 15:26:46 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	get_builtin(char *name)
{
	return NULL;
}

int	path_or_builtin(t_cmd *cmd)
{
	cmd->builtin = get_builtin(cmd->args->dynamic_str.bytes);
	if (cmd->builtin != NULL)
		return (0);
	cmd->path = cmd->args->dynamic_str.bytes;
	return (0);
}
