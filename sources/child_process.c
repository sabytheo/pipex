/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:08:56 by tsaby             #+#    #+#             */
/*   Updated: 2025/02/26 15:28:56 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_first(pid_t pid, t_pipex *pipou, char **envp)
{
	if (pid < 0)
	{
		close_fds(pipou);
		error("Error !\n Fork");
	}
	if (pid == 0)
	{
		dup2(pipou->in_fd, STDIN_FILENO);
		dup2(pipou->fd[1], STDOUT_FILENO);
		close_fds(pipou);
		exec_cmd(pipou->cmd1, envp);
	}
}

void	child_last(pid_t pid, t_pipex *pipou, char **envp)
{
	if (pid < 0)
	{
		close_fds(pipou);
		error("Error !\n Fork");
	}
	if (pid == 0)
	{
		dup2(pipou->fd[0], STDIN_FILENO);
		dup2(pipou->out_fd, STDOUT_FILENO);
		close_fds(pipou);
		exec_cmd(pipou->cmd2, envp);
	}
}
