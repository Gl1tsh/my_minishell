/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:10 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/10 08:43:51 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		failed;

	if (args[1] == NULL)
		failed = chdir(get_env_var(env, "HOME"));
	else
	{
		if (args[1][0] == '~' && args[1][1] != '\0')
			failed = chdir(get_env_var(env, "HOME"));
		else if (args[1][0] == '~')
		{
			path = (ft_strjoin(get_env_var(env, "HOME"), args[1] + 1));
			failed = chdir(path);
			free(path);
		}
		else
			failed = chdir(args[1]);
	}
	if (failed)
		return (perror_return("cd", 1));
	update_env_pwd(env);
	return (0);
}
