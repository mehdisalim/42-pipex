/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:10:57 by esalim            #+#    #+#             */
/*   Updated: 2023/01/21 17:11:01 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(int pfd[2], char **av, char **ev)
{
	char	**commands;
	int		fd;

	commands = split_commands(av[2], ev);
	close(pfd[0]);
	if (access(av[1], F_OK) == -1)
	{
		ft_exit("No such file or directory", av[1], commands, 1);
	}
	fd = open(av[1], O_RDONLY);
	if (access(av[1], R_OK) == -1 || fd == -1)
		ft_exit("permission denied", av[1], commands, 126);
	dup2(fd, STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	if (execve(commands[0], commands, ev) != -1)
		ft_exit("execve fiald", av[1], commands, 1);
	free_paths(commands);
	close(fd);
	exit(0);
}

static char	*get_path(char ***command)
{
	char	*str;
	char	*path;

	str = ft_strrchr(*command[0], '/');
	str += 1;
	path = ft_strdup(*command[0]);
	free(*command[0]);
	*command[0] = ft_strdup(str);
	return (path);
}

static void	parent_process(int pfd[2], char	**av, char **ev)
{
	char	**commands;
	char	*path;
	int		fd;

	close(pfd[1]);
	fd = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0666);
	commands = split_commands(av[3], ev);
	if (fd == -1)
		ft_exit("open fiald", av[1], commands, 1);
	dup2(pfd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	path = get_path(&commands);
	if (execve(path, commands, ev) != -1)
		ft_exit("execve fiald", av[1], commands, 1);
	free_paths(commands);
	close(fd);
}

void	pipex(char **av, char **ev)
{
	int	pfd[2];
	int	pid;

	if (pipe(pfd) == -1)
	{
		ft_printf("Error: Pipe faild\n");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Error: fork faild\n");
		exit(1);
	}
	if (pid == 0)
		child_process(pfd, av, ev);
	parent_process(pfd, av, ev);
	close(pfd[0]);
	close(pfd[1]);
}

int	main(int ac, char *av[], char *ev[])
{
	if (ac < 5)
	{
		ft_printf("the argemments most be 4 (infile cmd cmd outfile)");
		exit(1);
	}
	pipex(av, ev);
	return (0);
}
