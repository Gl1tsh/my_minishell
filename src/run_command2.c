/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:10:53 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/29 17:58:09 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_args(t_arg *args)
{
	char	**args_array;
	t_arg	*args_head;
	int		i;

	i = 0;
	args_head = args;
	while (args != NULL)
	{
		i++;
		args = args->next;
	}
	args_array = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (args_head != NULL)
	{
		args_array[i] = args_head->dynamic_str.bytes;
		args_head = args_head->next;
		i++;
	}
	args_array[i] = NULL;
	return (args_array);
}

int	exec_builtin(t_cmd *cmds, int in_fd, int *fd, t_env *env)
{
	int		exit_status;
	int		tmp_fd[2];
	char	**args;

	tmp_fd[0] = dup(STDIN_FILENO);
	tmp_fd[1] = dup(STDOUT_FILENO);
	if (redirect(in_fd, STDIN_FILENO) != 0)
		return (1);
	if (redirect(fd[1], STDOUT_FILENO) != 0)
		return (1);
	args = convert_args(cmds->args);
	exit_status = cmds->builtin(args, env);
	free(args);
	if (redirect(tmp_fd[0], STDIN_FILENO) != 0)
		return (1);
	if (redirect(tmp_fd[1], STDOUT_FILENO) != 0)
		return (1);
	return (exit_status);
}

int	exec_cmd(t_cmd *cmds, int in_fd, int *fd, t_env *env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (perror_return("exec_cmd", -1));
	if (pid == 0)
	{
		safe_close(fd[0]);
		if (redirect(in_fd, STDIN_FILENO) != 0)
			exit(127);
		if (redirect(fd[1], STDOUT_FILENO) != 0)
			exit(127);
		execve(cmds->path, convert_args(cmds->args), *env);
		perror("exec");
		exit(127);
	}
	safe_close(fd[1]);
	safe_close(in_fd);
	return (pid);
}

int	setup_pipe(t_cmd *cmds, int out_fd, int *fd)
{
	if (cmds->next == NULL)
	{
		fd[0] = -1;
		fd[1] = out_fd;
		return (0);
	}
	if (pipe(fd) == -1)
		return (perror_return("setup_pipe", 1));
	return (0);
}

int	exec_pipeline(t_cmd *cmds, int in_fd, int out_fd, t_env *env)
{
	int	fd[2];
	int	pid;
	int	status;

	if (setup_pipe(cmds, out_fd, fd) != 0)
		return (1);
	if (cmds->builtin != NULL)
	{
		pid = exec_builtin(cmds, in_fd, fd, env);
		if (pid != 0)
			return (pid);
	}
	else
	{
		pid = exec_cmd(cmds, in_fd, fd, env);
		if (pid < 0)
			return (1);
	}
	if (cmds->next != NULL)
		return (exec_pipeline(cmds->next, fd[0], out_fd, env));
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
