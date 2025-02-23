/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:38:19 by tsaby             #+#    #+#             */
/*   Updated: 2025/02/23 16:28:44 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_path(char *arg, char **envp)
{
	char	**path_arg;
	char	*path;
	char 	*temp;
	int		i;

	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	if(!envp[i])
		return(NULL);
	path_arg = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_arg[i])
	{
		temp = ft_strjoin(path_arg[i], "/");
		if (!temp)
		{
    		free_tab(path_arg);
    		return (NULL);
		}
		path = ft_strjoin(temp, arg);
		free(temp);
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
void	init_struct(t_pipex *pipou, char **argv)
{
	pipou->in_fd = open_input(argv[1]);
	if(!pipou->in_fd)
		error("Error !\n open input");
	pipou->out_fd = open_output(argv[4]);
	if(!pipou->out_fd)
		error("Error !\n open output");
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		free_tab(args);
		error("Error !\n Split");
	}
	path = find_path(args[0], envp);
	if (!path)
	{
		free_tab(args);
		error("Error !\n PATH");
	}
	execve(path, args, envp);
	free_tab(args);
	free(path);
	error("Error !\n execve");
}

void	pipex(t_pipex *pipou, char **argv, char **envp)
{
	pid_t	pid;
	char	*cmd1;
	char	*cmd2;

	cmd1 =  argv[2];
	cmd2 =  argv[3];
	if (pipe(pipou->fd) < 0)
	{
		close_fds(pipou);
		error("Error !\n Pipe");
	}
	pid = fork();
	if (pid < 0)
	{
		close_fds(pipou);
		error("Error !\n Fork");
	}
	if (pid == 0)
	{
		close(pipou->fd[0]);
		dup2(pipou->in_fd, STDIN_FILENO);
		dup2(pipou->fd[1], STDOUT_FILENO);
		exec_cmd(cmd1, envp);
	}
	else
	{
		close(pipou->fd[1]);
		dup2(pipou->fd[0], STDIN_FILENO);
		dup2(pipou->out_fd, STDOUT_FILENO);
		exec_cmd(cmd2, envp);
	}
	close_fds(pipou);
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipou;

	if (argc == 5)
	{
		init_struct(&pipou, argv);
		pipex(&pipou, argv, envp);
		close_fds(&pipou);
	}
	else
	{
		write(2, "Error !\n<file1> <cmd1> <cmd2> <file2>\n", 39);
		return (1);
	}
	return (0);
}
