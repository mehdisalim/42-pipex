/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:02:29 by esalim            #+#    #+#             */
/*   Updated: 2022/12/24 20:08:02 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(int pfd[2], char **av)
{
	char	**commands;

	commands = split_commands(av[2]);
	close(pfd[0]);
	int fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_with_error("open() error !!");
	dup2(fd, STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	execve(commands[0], commands, 0);
	close(fd);
	exit(0);
}

void	parent_process(int pfd[2], char	**av)
{
	char	**commands;

	commands = split_commands(av[3]);
	close(pfd[1]);
	int fd = open(av[4], O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
		exit_with_error("open() error !!");
	dup2(pfd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	execve(commands[0], commands, 0);
	close(fd);
}

void	pipex(char **av)
{

	int pfd[2];
	if (pipe(pfd) == -1)
		exit_with_error("pipe() error !!");
	int pid = fork();
	if (pid == -1)
		exit_with_error("fork() error !!");
	if (pid == 0)
		child_process(pfd, av);
	wait(NULL);
	parent_process(pfd, av);
}

int	main(int ac, char *av[])
{
	if (ac < 5)
		exit_with_error("the argemments most be 4 (infile cmd cmd outfile)");
	pipex(av);
}
