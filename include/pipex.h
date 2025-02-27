/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:14:18 by tsaby             #+#    #+#             */
/*   Updated: 2025/02/27 16:19:01 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	int		fd[2];
	int		in_fd;
	int		out_fd;
	char	*cmd1;
	char	*cmd2;

}			t_pipex;

int			error(const char *str);
void		free_tab(char **tab);
void		close_fds(t_pipex *pipou);
int			open_input(char *file1);
int			open_output(char *file2);

void		child_first(pid_t pid, t_pipex *pipou, char **envp);
void		child_last(pid_t pid, t_pipex *pipou, char **envp);
void		exec_cmd(char *cmd, char **envp);

#endif
