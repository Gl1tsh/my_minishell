/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:21 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/29 15:56:46 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **args, t_env *env)
{
	int	i;
	int	option_n;

	(void)env;
	option_n = args[1] && ft_strncmp(args[1], "-n", 2) == 0;
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
