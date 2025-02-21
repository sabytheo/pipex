/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:13:57 by tsaby             #+#    #+#             */
/*   Updated: 2025/02/20 16:14:51 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int open_input(char *file1)
{
	int fd;

	fd = open(file1, O_RDONLY);
	if(fd < 0)
		error("Error !\n Files  1");
	return (fd);
}

int open_output(char *file2)
{
	int fd;

	fd = open(file2, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if(fd < 0)
		error("Error !\n Files 2");
	return (fd);
}

int error(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
