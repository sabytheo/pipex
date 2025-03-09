/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:14:18 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/09 13:14:09 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		count_pipe;
	char	**cmd;
	int		count_cmd;
	pid_t	*pid;
	char	**path_arg;
	char	**args;
	int (*fd_pipes)[2];

}			t_pipex;

int			error(const char *str, t_pipex *pipou);
void		free_all(t_pipex *pipou, int i);
void		close_fds(t_pipex *pipou, int (*fd_pipes)[2]);
int			open_input(char *file1);
int			open_output(char *file2);
void		multiple_pipe(t_pipex *pipou, int (*fd_pipes)[2]);
char		*get_a_path(char *path_arg, char *arg);
void	free_tab(char **tab);
void	init_pipe(t_pipex *pipou);

#endif
