/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:13:57 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/11 11:55:24 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_all(t_pipex *pipex, int i)
{
	if (pipex->cmd)
	{
		while (pipex->cmd[i])
			free(pipex->cmd[i++]);
		free(pipex->cmd);
	}
	i = 0;
	if (pipex->args)
	{
		while (pipex->args[i])
			free(pipex->args[i++]);
		free(pipex->args);
	}
	i = 0;
	if (pipex->path_arg)
	{
		while (pipex->path_arg[i])
			free(pipex->path_arg[i++]);
		free(pipex->path_arg);
	}
	if (pipex->pid)
		free(pipex->pid);
	if (pipex->fd_pipes)
		free(pipex->fd_pipes);
}

int	open_input(char *file1)
{
	int	fd;

	fd = open(file1, O_RDONLY);
	if (fd == -1)
		perror("Error !\n");
	if (access(file1, F_OK | R_OK) == -1)
		fd = -2;
	return (fd);
}

int	open_output(char *file2)
{
	int	fd;

	fd = open(file2, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		perror("Error !\n");
	if (access(file2, F_OK | W_OK) == -1)
		fd = -2;
	return (fd);
}

int	error(const char *str, t_pipex *pipex)
{
	perror(str);
	free_all(pipex, 0);
	exit(EXIT_FAILURE);
}

void	close_fds(t_pipex *pipex, int (*fd_pipes)[2])
{
	int	j;

	j = 0;
	while (j <= pipex->count_pipe)
	{
		close(fd_pipes[j][0]);
		close(fd_pipes[j][1]);
		j++;
	}
	if (pipex->in_fd > 0)
		close(pipex->in_fd);
	if (pipex->out_fd > 0)
		close(pipex->out_fd);
}
