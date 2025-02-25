/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:14:18 by tsaby             #+#    #+#             */
/*   Updated: 2025/02/25 14:58:23 by tsaby            ###   ########.fr       */
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
	int	fd[2];
	int	in_fd;
	int	out_fd;
	int count_pipe;
	char **cmd;

}		t_pipex;

int		error(const char *str);
void	free_tab(char **tab);
void	close_fds(t_pipex *pipou);
int		open_input(char *file1);
int		open_output(char *file2);

#endif
