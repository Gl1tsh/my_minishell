/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:10:25 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/10 09:10:47 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **args, t_env *env)
{
	args++;
	while (*args)
	{
		if (!is_valid_var_name(*args))
			return (perror_return("invalid var name", 1));
		remove_env_var(env, *args);
		args++;
	}
	return (0);
}
