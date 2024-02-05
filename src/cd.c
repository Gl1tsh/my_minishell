/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:10 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/05 15:38:09 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **args, char **env)
{
	(void)env;
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
