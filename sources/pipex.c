/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:38:19 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/11 11:55:24 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *arg, char **envp, int i)
{
	char	**path_arg;
	char	*path;

	while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	if (!envp[i])
		return (NULL);
	path_arg = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_arg != NULL && path_arg[i] && arg)
	{
		path = get_a_path(path_arg[i], arg);
		if (!path)
			return (free_tab(path_arg), NULL);
		if (access(path, X_OK) == 0)
		{
			free_tab(path_arg);
			return (path);
		}
		free(path);
		i++;
	}
	free_tab(path_arg);
	return (NULL);
}

void	init_struct(t_pipex *pipex, char **argv)
{
	pipex->cmd1 = argv[2];
	pipex->cmd2 = argv[3];
	pipex->error = 0;
	pipex->in_fd = open_input(argv[1]);
	pipex->out_fd = open_output(argv[4]);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*path;
	int		i;

	i = 0;
	args = ft_split(cmd, ' ');
	if (!args)
	{
		free_tab(args);
		write(2, "Error !\nsplit issues\n", 22);
		exit(EXIT_FAILURE);
	}
	path = find_path(args[0], envp, i);
	if (!path)
	{
		free_tab(args);
		write(2, "Error !\ncommand not found\n", 27);
		exit(EXIT_FAILURE);
	}
	execve(path, args, envp);
	free_tab(args);
	free(path);
	error("Error !\n execve");
}

void	pipe_and_fork(t_pipex *pipex, char **envp)
{
	pid_t	pid;
	pid_t	pid2;

	if (pipe(pipex->fd) < 0)
	{
		close_fds(pipex);
		error("Error !\nPipe\n");
	}
	if (pipex->in_fd > 0)
	{
		pid = fork();
		child_first(pid, pipex, envp);
	}
	if (pipex->out_fd > 0)
	{
		pid2 = fork();
		child_last(pid2, pipex, envp);
	}
	else
		pipex->error = 1;
	close_fds(pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	pid;

	pid = 0;
	if (argc == 5)
	{
		init_struct(&pipex, argv);
		pipe_and_fork(&pipex, envp);
		close_fds(&pipex);
	}
	else
	{
		write(2, "Error !\n<file1> <cmd1> <cmd2> <file2>\n", 39);
		return (1);
	}
	while (pid != -1)
		pid = wait(NULL);
	if (pipex.error == 1)
		return (1);
	return (0);
}
