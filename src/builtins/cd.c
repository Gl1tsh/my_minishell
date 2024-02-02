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

#include <string.h>
#define ft_strcmp strcmp
void	update_env_pwd(t_env *env)
{
	char	*cwd;
	char	*pwd;
	char	*old_pwd;

	cwd = getcwd(NULL, 0);
	if (ft_strcmp(cwd, get_env_var(env, "PWD")) != 0)
	{
		old_pwd = ft_strjoin("OLDPWD=", get_env_var(env, "PWD"));
		pwd = ft_strjoin("PWD=", cwd);
		update_env_var(env, old_pwd);
		update_env_var(env, pwd);
		free(old_pwd);
		free(pwd);
	}
	free(cwd);
}

int	builtin_cd(char **args, t_env *env)
{
	char	*path;

	if (args[1] == NULL)
		chdir(get_env_var(env, "HOME"));
	else
	{
		if (args[1][0] == '~' && args[1][1] == '\0')
			chdir(get_env_var(env, "HOME"));
		else if (args[1][0] == '~')
		{
			path = ft_strjoin(get_env_var(env, "HOME"), args[1] + 1);
			chdir(path);
			free(path);
		}
		else
			chdir(args[1]);
	}
	update_env_pwd(env);
	return (0);
}
