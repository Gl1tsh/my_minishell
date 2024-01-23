/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:55:07 by tomuller          #+#    #+#             */
/*   Updated: 2024/01/20 16:03:09 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char **args, int in_fd, int out_fd, char **env)
{
	int	i;
	int	option_n;

	option_n = ft_strncmp(args[1], "-n", 2) == 0;
	if (option_n)
		i = 2;
	else
		i = 1;
	while (args[i])
		printf("%s ", args[i++]);
	if (!option_n)
		printf("\n");
}
