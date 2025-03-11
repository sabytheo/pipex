/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:08:56 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/11 11:55:24 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_first(pid_t pid, t_pipex *pipex, char **envp)
{
	if (pid < 0)
	{
		close_fds(pipex);
		error("Error !\n Fork");
	}
	if (pid == 0)
	{
		dup2(pipex->in_fd, STDIN_FILENO);
		dup2(pipex->fd[1], STDOUT_FILENO);
		close_fds(pipex);
		exec_cmd(pipex->cmd1, envp);
	}
}

void	child_last(pid_t pid, t_pipex *pipex, char **envp)
{
	if (pid < 0)
	{
		close_fds(pipex);
		error("Error !\n Fork");
	}
	if (pid == 0)
	{
		dup2(pipex->fd[0], STDIN_FILENO);
		dup2(pipex->out_fd, STDOUT_FILENO);
		close_fds(pipex);
		exec_cmd(pipex->cmd2, envp);
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
