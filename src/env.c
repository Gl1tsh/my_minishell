/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:27 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/23 17:22:29 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(char **args, int in_fd, int out_fd, char **env)
{
	int			i;

	i = 0;
	while (env[i++] != NULL)
		printf("%s\n", env[i]);
}
