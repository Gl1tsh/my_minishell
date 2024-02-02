/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:27 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/29 15:49:39 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **args, t_env *the_env)
{
	int		i;
	char	**env;

	env = *the_env;
	i = 0;
	while (env[i] != NULL)
	{
		if (env[i][0] != '?')
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}