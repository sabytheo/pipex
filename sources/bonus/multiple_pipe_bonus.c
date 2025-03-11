/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:09:26 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/11 11:55:24 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	multiple_pipe(t_pipex *pipex, int (*fd_pipes)[2])
{
	int	i;

	i = 0;
	while (i < pipex->count_cmd)
	{
		if (pipe(fd_pipes[i]) == -1)
		{
			free_all(pipex, 0);
			error("Error !\n Pipes ", pipex);
		}
		i++;
	}
}

char	*get_a_path(char *path_arg, char *arg)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(path_arg, "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, arg);
	if (!path)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (path);
}

void	init_pipe(t_pipex *pipex)
{
	pipex->pid = malloc(sizeof(pid_t) * pipex->count_cmd);
	if (!pipex->pid)
	{
		write(2, "Error !\nMalloc issues\n", 22);
		free_all(pipex, 0);
		exit(EXIT_FAILURE);
	}
	pipex->fd_pipes = malloc(sizeof(int [2]) * pipex->count_cmd);
	if (!pipex->fd_pipes)
	{
		close_fds(pipex, pipex->fd_pipes);
		error("Error !\n Malloc", pipex);
	}
}

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
