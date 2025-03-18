/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:38:19 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/18 16:26:16 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_path(char *arg, char **envp, int i, t_pipex *pipex)
{
	char	*path;

	while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	if (!envp[i])
		return (NULL);
	if (access(arg, X_OK) == 0)
		return (arg);
	pipex->path_arg = ft_split(envp[i] + 5, ':');
	i = 0;
	while (pipex->path_arg != NULL && pipex->path_arg[i] && arg)
	{
		path = get_a_path(pipex->path_arg[i], arg);
		if (!path)
			return (free_all(pipex, 0), NULL);
		if (access(path, X_OK) == 0)
		{
			free_tab(pipex->path_arg);
			return (path);
		}
		free(path);
		i++;
	}
	free_all(pipex, 0);
	return (NULL);
}

void	init_struct(t_pipex *pipex, char **argv, int argc)
{
	int	i;

	pipex->args = NULL;
	pipex->path_arg = NULL;
	pipex->count_cmd = argc - 3;
	pipex->count_pipe = pipex->count_cmd - 1;
	i = 2;
	pipex->cmd = (char **)malloc(sizeof(char *) * (pipex->count_cmd + 1));
	if (!pipex->cmd)
	{
		write(2, "Error !\n malloc failed\n", 24);
		exit(EXIT_FAILURE);
	}
	while (i <= argc - 2)
	{
		pipex->cmd[i - 2] = ft_strdup(argv[i]);
		i++;
	}
	pipex->cmd[i - 2] = NULL;
	pipex->in_fd = open_input(argv[1]);
	pipex->out_fd = open_output(argv[argc - 1]);
	init_pipe(pipex);
}

void	exec_cmd(char *cmd, char **envp, t_pipex *pipex)
{
	char	*path;
	int		i;

	i = 0;
	pipex->args = ft_split(cmd, ' ');
	if (!pipex->args)
	{
		write(2, "Error !\n split issues\n", 23);
		exit(EXIT_FAILURE);
	}
	path = find_path(pipex->args[0], envp, i, pipex);
	if (!path)
	{
		write(2, "Error !\n command not found\n", 28);
		exit(EXIT_FAILURE);
	}
	execve(path, pipex->args, envp);
	free_all(pipex, 0);
	free(path);
	error("Error !\n execve", pipex);
}

void	pipex_main(t_pipex *pipex, char **envp, int i)
{
	multiple_pipe(pipex, pipex->fd_pipes);
	while (++i < pipex->count_cmd)
	{
		if ((i == 0 && pipex->in_fd < 0) || (i == pipex->count_pipe
				&& pipex->out_fd < 0))
			continue ;
		pipex->pid[i] = fork();
		if (pipex->pid[i] < 0)
			error("Error !\n Fork", pipex);
		if (pipex->pid[i] == 0)
		{
			if (i == 0)
				dup2(pipex->in_fd, STDIN_FILENO);
			else
				dup2(pipex->fd_pipes[i - 1][0], STDIN_FILENO);
			if (i == pipex->count_pipe)
				dup2(pipex->out_fd, STDOUT_FILENO);
			else
				dup2(pipex->fd_pipes[i][1], STDOUT_FILENO);
			close_fds(pipex, pipex->fd_pipes);
			exec_cmd(pipex->cmd[i], envp, pipex);
		}
	}
	close_fds(pipex, pipex->fd_pipes);
	free_all(pipex, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	pid;
	int		i;

	i = -1;
	pid = 0;
	if (argc >= 5)
	{
		init_struct(&pipex, argv, argc);
		pipex_main(&pipex, envp, i);
	}
	else
	{
		write(2, "Error !\n<file1> <cmd1> <cmd2> <file2>\n", 39);
		return (1);
	}
	while (pid != -1)
		pid = wait(NULL);
	return (0);
}
