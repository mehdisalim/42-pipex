/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:02:29 by esalim            #+#    #+#             */
/*   Updated: 2022/12/25 15:16:25 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**sep_cmd(char *s)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = malloc(3 * sizeof(char *));
	if (!cmds)
		exit(0);
	while (s[i])
		if (s[i++] == ' ')
			break ;
	cmds[0] = ft_substr(s, 0, i);
	cmds[1] = ft_substr(s, i, ft_strlen(s));
	if (cmds[1] != 0)
		cmds[2] = 0;
	return (cmds);
}

void	child_process(int pfd[2], char **av)
{
	char	**commands;

	commands = sep_cmd(av[2]);
	close(pfd[0]);
	int fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(-1);
	}
	dup2(fd, STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	execve(commands[0], commands, 0);
	close(fd);
	exit(0);
}

void	parent_process(int pfd[2], char	**av)
{
	char	**commands;

	commands = sep_cmd(av[3]);
	close(pfd[1]);
	int fd = open(av[4], O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("Error");
		exit(-1);
	}
	dup2(pfd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	execve(commands[0], commands, 0);
	close(fd);
}

void	pipex(char **av)
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
