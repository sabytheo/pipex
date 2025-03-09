/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:09:26 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/09 13:37:33 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	multiple_pipe(t_pipex *pipou, int (*fd_pipes)[2])
{
	int	i;

	i = 0;
	while (i < pipou->count_cmd)
	{
		if (pipe(fd_pipes[i]) == -1)
		{
			free_all(pipou, 0);
			error("Error !\n Pipes ", pipou);
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

void	init_pipe(t_pipex *pipou)
{
	pipou->pid = malloc(sizeof(pid_t) * pipou->count_cmd);
	if (!pipou->pid)
	{
		write(2, "Error !\nMalloc issues\n", 22);
		free_all(pipou, 0);
		exit(EXIT_FAILURE);
	}
	pipou->fd_pipes = malloc(sizeof(int [2]) * pipou->count_cmd);
	if (!pipou->fd_pipes)
	{
		close_fds(pipou, pipou->fd_pipes);
		error("Error !\n Malloc", pipou);
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
