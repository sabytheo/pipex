/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:09:26 by tsaby             #+#    #+#             */
/*   Updated: 2025/02/27 21:10:16 by tsaby            ###   ########.fr       */
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
				free_tab(pipou->cmd);
				error("Error !\n Pipes ",pipou);
			}
		i++;
	}
}
