/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:21 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/10 08:36:42 by nagiorgi         ###   ########.fr       */
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
	{
		if (args[i + 1])
			printf("%s ", args[i++]);
		else
			printf("%s", args[i++]);
	}
	if (!option_n)
		printf("\n");
	return (0);
}
