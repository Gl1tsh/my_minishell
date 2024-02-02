/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:22:47 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/24 15:56:52 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <fcntl.h>

void	heredoc_signal_handler(int sig_num)
{
	(void)sig_num;
	close(0);
}

char	*generate_pid_string(char *target)
{
	int	pid;
	int	i;

	pid = getpid();
	i = 0;
	while (i < 8)
	{
		target[i++] = (pid & 0xF) + 'A';
		pid = pid >> 4;
	}
	target[8] = 0;
	return (target);
}

int	read_heredoc(t_dstr *heredoc, char *eos)
{
	char	*line;
	int		stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_signal_handler);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
		{
			redirect(stdin_copy, STDIN_FILENO);
			signal(SIGINT, parsing_signal_handler);
			return (1);
		}
		if (ft_strcmp(line, eos) == 0)
			break ;
		dstr_append(heredoc, line, ft_strlen(line));
		dstr_append(heredoc, "\n", 1);
	}
	close(stdin_copy);
	signal(SIGINT, parsing_signal_handler);
	return (0);
}

int	process_heredoc(t_cmd *cmds)
{
	char	temp_filename[9];
	char	*temp_pathname;
	char	*temp_dirname;
	int		fd;
	t_dstr	heredoc;

	if (cmds->dirin != NULL && cmds->dirin_mode == DIRIN_MODE_HEREDOC)
	{
		dstr_allocate(&heredoc, 128);
		if (read_heredoc(&heredoc, cmds->dirin) != 0)
		{
			dstr_free(&heredoc);
			return (1);
		}
		temp_dirname = getenv("TMPDIR");
		if (temp_dirname == NULL)
			temp_dirname = "/tmp";
		temp_pathname = join_path(temp_dirname, generate_pid_string(temp_filename));
		fd = open(temp_pathname, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		write(fd, heredoc.bytes, ft_strlen(heredoc.bytes));
		close(fd);
		free(cmds->dirin);
		dstr_free(&heredoc);
		cmds->dirin = temp_pathname;
	}
	return (0);
}
