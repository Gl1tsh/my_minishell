/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:10:29 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/10 09:10:32 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(char **args, t_env *env)
{
	args++;
	while (*args)
	{
		if (!is_valid_var_name(*args))
			return (perror_return("invalid var name", 1));
		update_env_var(env, *args);
		args++;
	}
	return (0);
}