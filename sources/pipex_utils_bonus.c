/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:13:57 by tsaby             #+#    #+#             */
/*   Updated: 2025/02/27 20:52:15 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	error(const char *str, t_pipex *pipou)
{
	perror(str);
	free_tab(pipou->cmd);
	exit(EXIT_FAILURE);
}

void	close_fds(t_pipex *pipou, int (*fd_pipes)[2])
{
	int j;

	j = 0;
	while (j <= pipou->count_pipe)
	{
		if(fd_pipes[j][0] > 0 && fd_pipes[j][1] > 0)
		{
			close(fd_pipes[j][0]);
			close(fd_pipes[j][1]);
		}
		j++;
	}
    if (pipou->in_fd > 0)
        close(pipou->in_fd);
    if (pipou->out_fd > 0)
        close(pipou->out_fd);

}


