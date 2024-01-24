/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:10:53 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/23 17:23:15 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

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

char	**copy_args(t_alist *arg_list)
{
	char	**args;
	int		arg_count;
	t_arg	*current_arg;
	int		i;

	arg_count = alist_size(arg_list);
	args = malloc((arg_count + 1) * sizeof(char *));
	i = 0;
	current_arg = (t_arg *)alist_get_head(arg_list);
	while (current_arg)
	{
		args[i++] = current_arg->string.bytes;
		current_arg = (t_arg *)alist_get_succ((t_anode *)current_arg);
	}
	args[i] = NULL;
	return args;
}

void	exec(t_cmd *cmd, char **env)
{
	cmd->path = ((t_arg *)alist_get_head(&cmd->args))->string.bytes;
	execve(cmd->path, copy_args(&cmd->args), env);
	write(STDERR_FILENO, "exec : command not found\n", 20);
	exit(127);
}

void	safe_close(int fd)
{
	if (fd >= 2)
		close(fd);
}

void	cmd_signal_handler(int sig_num)
{
	(void)sig_num;
	//rien mettre
}

void redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) != -1)
			safe_close(oldfd);
		else
		{
			perror("dup2");
			exit(1);
		}
	}
}

int	exec_pipeline(t_cmd *cmds, int in_fd, int out_fd, char **env)
{
	int fd[2];
	int	pid;
	int	status;

	fprintf(stderr, "%d > exec_pipeline: running %s\n", getpid(), cmds->path);
	if (alist_get_succ((t_anode *)cmds) == NULL)
	{
		fd[0] = -1;
		fd[1] = out_fd;
	}
	else
	{
		if (pipe(fd) == -1)
			return 111;
	}
	if (cmds->builtin != NULL)
	{
		cmds->builtin(&cmds->args, in_fd, fd[1], env);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return 112;
		if (pid == 0)
		{
			safe_close(fd[0]);
			redirect(in_fd, STDIN_FILENO);
			redirect(fd[1], STDOUT_FILENO);
			exec(cmds, env);
		}
	}
	safe_close(fd[1]);
	safe_close(in_fd);
	if (alist_get_succ((t_anode *)cmds) != NULL)
		return exec_pipeline((t_cmd *)alist_get_succ((t_anode *)cmds), fd[0], out_fd, env);
	waitpid(pid, &status, 0);
	return 0;
}

int	run_commands(t_alist *commands, char **env)
{
    // Run a pre-flight converting `command` to its path and calling `access`
    // (what to do when one of the command in the pipeline is an builtin?)
	signal(SIGINT, &cmd_signal_handler);
	signal(SIGQUIT, &cmd_signal_handler);
	fprintf(stderr, "run_commands: before\n");
    int error = exec_pipeline((t_cmd *)alist_get_head(commands), STDIN_FILENO, STDOUT_FILENO, env);
	if (error > 100)
	{
		fprintf(stderr, "run_commands: piping failed %d\n", error);
		perror(NULL);
	}
    fprintf(stderr, "run_commands: after\n");
	return 0;
}
