/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:02:29 by esalim            #+#    #+#             */
/*   Updated: 2022/12/28 17:21:51 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(int pfd[2], char **av, char **ev)
{
	char	**commands;

	commands = split_commands(av[2], ev);
	close(pfd[0]);
	if (access(av[1], R_OK) == -1)
	{
	  write(2, "Error:  No such file or directory", 33);
	  exit(1);
	}
	int fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error:  No such file or directory", 33);
	   	exit(1);
	}
	dup2(fd, STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	if (execve(commands[0], commands, 0) != -1)	
		write(2, "Execve error", 12);
	close(fd);
	exit(0);
}

void	parent_process(int pfd[2], char	**av, char **ev)
{
	char	**commands;

	commands = split_commands(av[3], ev);
	close(pfd[1]);
	int fd = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0666);
	if (fd == -1)
	{
		write(2, "Error:  No such file or directory", 33);
	   	exit(1);
	}
	dup2(pfd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	if (execve(commands[0], commands, ev) != -1)
		write(2, "Execve error", 12);
	close(fd);
}

void	pipex(char **av, char **ev)
{

	int pfd[2];
	if (pipe(pfd) == -1)
	{
		perror("Error");
		exit(-1);
	}
	int pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(-1);
	}
	if (pid == 0)
		child_process(pfd, av, ev);
	wait(NULL);
	parent_process(pfd, av, ev);
}

int	main(int ac, char *av[], char *ev[])
{
	if (ac < 5)
	{
		exit_with_error("the argemments most be 4 (infile cmd cmd outfile)", 127);
		exit(1);
	}
//	int i = -1;
//	while (ev[++i])
//		ft_printf("%s\n", ev[i]);
	pipex(av, ev);
}
