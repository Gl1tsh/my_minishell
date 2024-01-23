/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:10 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/23 17:22:13 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(char **args, int in_fd, int out_fd, char **env)
{
	char	**path;

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
}
