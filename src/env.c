/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:27 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/07 11:02:49 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **args, char **env)
{
	int	i;

	(void)args;
	i = 0;
	while (env[i++] != NULL)
		printf("%s\n", env[i]);
	return (0);
}
