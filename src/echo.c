/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:21 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/05 15:42:17 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **args, char **env)
{
	int	i;
	int	option_n;

	(void)env;
	option_n = ft_strncmp(args[1], "-n", 2) == 0;
	if (option_n)
		i = 2;
	else
		i = 1;
	while (args[i])
		printf("%s ", args[i++]);
	if (!option_n)
		printf("\n");
	return (0);
}
