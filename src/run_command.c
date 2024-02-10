/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:10:53 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/10 09:17:13 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	safe_close(int fd)
{
	if (fd >= 2)
		close(fd);
}

void	cmd_signal_handler(int sig_num)
{
	if (sig_num == SIGQUIT)
		printf("Quit: %d\n", sig_num);
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

int	setup_redirections(t_cmd *cmds, int *fd)
{
	if (cmds->dirin != NULL)
	{
		fd[0] = open(cmds->dirin, O_RDONLY);
		if (fd[0] < 0)
			return (perror_return("redirection", 1));
		if (cmds->dirin_mode == DIRIN_MODE_HEREDOC)
			unlink(cmds->dirin);
		fd[2] = dup(STDIN_FILENO);
	}
	while (cmds->next != NULL)
		cmds = cmds->next;
	if (cmds->dirout != NULL)
	{
		fd[1] = open(cmds->dirout, cmds->dirout_mode, 0777);
		if (fd[1] < 0)
		{
			safe_close(fd[0]);
			safe_close(fd[2]);
			return (perror_return("redirection", 1));
		}
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
