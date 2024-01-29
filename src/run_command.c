/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:10:53 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/29 16:07:59 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int 	i;

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

void	exec(t_cmd *cmd, char **env)
{
	execve(cmd->path, convert_args(cmd->args), env);
	perror("exec");
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

int	setup_pipe(t_cmd *cmds, int out_fd, int *fd)
{
	if (cmds->next == NULL)
	{
		fd[0] = -1;
		fd[1] = out_fd;
		return (0);
	}
	if (pipe(fd) == -1)
	{
		perror("setup_pipe");
		return (1);
	}
	return (0);
}

int	exec_pipeline(t_cmd *cmds, int in_fd, int out_fd, char **env)
{
	int fd[2];
	int	pid;
	int	status;

	fprintf(stderr, "exec_pipeline: running\n");
	if (setup_pipe(cmds, out_fd, fd) != 0)
		return (1);
	if (cmds->builtin != NULL)
	{
		cmds->builtin(convert_args(cmds->args), env);
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
	if (cmds->next != NULL)
		return (exec_pipeline(cmds->next, fd[0], out_fd, env));
	waitpid(pid, &status, 0);
	return 0;
}

int	run_commands(t_cmd *commands, char **env)
{
	signal(SIGINT, &cmd_signal_handler);
	signal(SIGQUIT, &cmd_signal_handler);
	// fprintf(stderr, "run_commands: before\n");
	return (exec_pipeline(commands, STDIN_FILENO, STDOUT_FILENO, env));
}
