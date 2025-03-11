/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:13:57 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/11 11:55:24 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
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

int	error(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	close_fds(t_pipex *pipex)
{
	if (pipex->in_fd > 0)
		close(pipex->in_fd);
	if (pipex->out_fd > 0)
		close(pipex->out_fd);
	if (pipex->fd[0] > 0)
		close(pipex->fd[0]);
	if (pipex->fd[1] > 0)
		close(pipex->fd[1]);
}
