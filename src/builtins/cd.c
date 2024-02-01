/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:10 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/29 15:56:34 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **args, t_env *env)
{
	if (args[1] == NULL)
		chdir(getenv("HOME"));
	else
	{
		if (args[1][0] == '~' && args[1][1] != '\0')
		{
			chdir(getenv("HOME"));
		}
		else if (args[1][0] == '~')
			chdir(ft_strjoin(getenv("HOME"), args[1] + 1));
		else
			chdir(args[1]);
	}
	return (0);
}
