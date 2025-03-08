/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:38:19 by tsaby             #+#    #+#             */
/*   Updated: 2025/03/08 17:51:12 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	init_struct(t_pipex *pipou, char **argv, int argc)
{
	int	i;

	pipou->count_cmd = argc - 3;
	pipou->count_pipe = pipou->count_cmd - 1;
	i = 2;
	pipou->cmd = (char **)malloc(sizeof(char *) * (pipou->count_cmd + 1));
	if (!pipou->cmd)
	{
		free_tab(pipou->cmd);
		write(2, "Error !\n malloc failed\n", 24);
		exit(EXIT_FAILURE);
	}
	while (i <= argc - 2)
	{
		pipou->cmd[i - 2] = ft_strdup(argv[i]);
		i++;
	}
	pipou->cmd[i - 2] = NULL;
	pipou->in_fd = open_input(argv[1]);
	pipou->out_fd = open_output(argv[argc - 1]);
}

void	exec_cmd(char *cmd, char **envp, t_pipex *pipou)
{
	char	**args;
	char	*path;
	int		i;

	i = 0;
	args = ft_split(cmd, ' ');
	if (!args)
	{
		free_tab(args);
		free_tab(pipou->cmd);
		write(2, "Error !\n split issues\n", 23);
		exit(EXIT_FAILURE);
	}
	path = find_path(args[0], envp, i);
	if (!path)
	{
		free_tab(args);
		free_tab(pipou->cmd);
		write(2, "Error !\n command not found\n", 28);
		exit(EXIT_FAILURE);
	}
	execve(path, args, envp);
	free_tab(args);
	free(path);
	error("Error !\n execve", pipou);
}

void	pipex(t_pipex *pipou, char **envp, int i)
{
	pid_t	pid[pipou->count_cmd];
	int		fd_pipes[pipou->count_cmd][2];

	multiple_pipe(pipou, fd_pipes);
	while (++i < pipou->count_cmd)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			error("Error !\n Fork", pipou);
		if (pid[i] == 0)
		{
			if (i == 0)
				dup2(pipou->in_fd, STDIN_FILENO);
			else
				dup2(fd_pipes[i - 1][0], STDIN_FILENO);
			if (i == pipou->count_pipe)
				dup2(pipou->out_fd, STDOUT_FILENO);
			else
				dup2(fd_pipes[i][1], STDOUT_FILENO);
			close_fds(pipou, fd_pipes);
			exec_cmd(pipou->cmd[i], envp, pipou);
		}
	}
	free_tab(pipou->cmd);
	close_fds(pipou, fd_pipes);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipou;
	pid_t	pid;
	int		i;

	i = -1;
	pid = 0;
	if (argc >= 5)
	{
		init_struct(&pipou, argv, argc);
		pipex(&pipou, envp, i);
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
