/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:38:19 by tsaby             #+#    #+#             */
/*   Updated: 2025/02/20 18:49:09 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *arg, char **envp)
{
	char	**path_arg;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	path_arg = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_arg[i])
	{
		path = ft_strjoin(path_arg[i], "/");
		path = ft_strjoin(path, arg);
		if (access(path, X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}
void	init_struct(t_pipex *pipou, char **argv)
{
	if (!(pipou->in_fd = open_input(argv[1])))
		error("Error !\n open input");
	if (!(pipou->out_fd = open_output(argv[4])))
		error("Error !\n open output");
}

void	exec_cmd(t_pipex *pipou, char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!(path = find_path(args[0], envp)))
		error("Error !\n PATH");
	dup2(pipou->fd[0], STDIN_FILENO);
	dup2(pipou->out_fd, STDOUT_FILENO);
	dup2(pipou->fd[1], STDOUT_FILENO);
	if (!(execve(path, args, envp)))
		error("Error !\n execve");
}

void	pipex(t_pipex *pipou, char **argv, char **envp)
{
	pid_t	pid;
	char	*cmd1;
	char	*cmd2;

	cmd1 =  ft_strdup(argv[2]);
	cmd2 =  ft_strdup(argv[3]);
	if (pipe(pipou->fd) < 0)
		error("Error !\n Pipe");
	pid = fork();
	if (pid < 0)
		error("Error !\n Fork");
	if (pid == 0)
	{
		close(pipou->fd[0]);
		exec_cmd(pipou, cmd1, envp);
	}
	else
	{
		close(pipou->fd[1]);
		exec_cmd(pipou, cmd2, envp);
		close(pipou->in_fd);
		close(pipou->out_fd);
		waitpid(pid, NULL, 0);
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipou;

	if (argc == 5)
	{
		init_struct(&pipou, argv);
		pipex(&pipou, argv, envp);
	}
	else
		write(2, "Error !\n<file1> <cmd1> <cmd2> <file2>\n", 39);
	return (0);
}
