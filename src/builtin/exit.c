/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:34 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/11 14:52:38 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_zero(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, t_env *env)
{
	int	exit_status;

	(void)env;
	if (args[1] != NULL)
	{
		if (is_only_zero(args[1]))
			return (0);

		exit_status = ft_atoi(args[1]);
		if (exit_status > 0 && exit_status <= 255)
			return (-exit_status);
		return (-255);
	}
	return (-1);
}
