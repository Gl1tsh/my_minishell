/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:10:53 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/29 17:58:09 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

/******************************************************************************
*                                                                             *
*   File: run_command.c                                                       *
*                                                                             *
*   Index:                                                                    *
*   1. exec - Executes a command with the provided environment                *
*   2. safe_close - Safely closes a file descriptor                           *
*   3. redirect - Redirects one file descriptor to another                    *
*   4. exec_pipeline - Executes a pipeline of commands                        *
*   5. run_commands - Runs a list of commands                                 *
*                                                                             *
******************************************************************************/

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

int	perror_return(char *message, int exit_status)
{
	perror(message);
	return (exit_status);
}

void	safe_close(int fd)
{
	if (fd >= 2)
		close(fd);
}

void	cmd_signal_handler(int sig_num)
{
	(void)sig_num;
}

int	redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) != -1)
			safe_close(oldfd);
		else
			return (perror_return("redirect", 1));
	}
	return (0);
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
		return (perror_return("exec_cmd", 1));
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
		exec_builtin(cmds, in_fd, fd, env);
		pid = 0;
	}
	else
		pid = exec_cmd(cmds, in_fd, fd, env);
	if (cmds->next != NULL)
		return (exec_pipeline(cmds->next, fd[0], out_fd, env));
	waitpid(pid, &status, 0);
	return (0);
}

int	setup_redirections(t_cmd *cmds, int *fd)
{
	if (cmds->dirin != NULL)
	{
		fd[0] = open(cmds->dirin, O_RDONLY);
		if (cmds->dirin_mode == DIRIN_MODE_HEREDOC)
			unlink(cmds->dirin);
		fd[2] = dup(STDIN_FILENO);
	}
	while (cmds->next != NULL)
		cmds = cmds->next;
	if (cmds->dirout != NULL)
	{
		fd[1] = open(cmds->dirout, cmds->dirout_mode, 0777);
		fd[3] = dup(STDOUT_FILENO);
	}
	return (0);
}

int	run_commands(t_cmd *commands, t_env *env)
{
	int	fd[4];
	int	exit_status;

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	fd[2] = -1;
	fd[3] = -1;
	exit_status = setup_redirections(commands, fd);
	if (exit_status == 0)
	{
		signal(SIGINT, &cmd_signal_handler);
		signal(SIGQUIT, &cmd_signal_handler);
		exit_status = exec_pipeline(commands, fd[0], fd[1], env);
	}
	signal(SIGINT, parsing_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (fd[2] > 0)
		redirect(fd[2], STDIN_FILENO);
	if (fd[3] > 0)
		redirect(fd[3], STDOUT_FILENO);
	return (exit_status);
}
