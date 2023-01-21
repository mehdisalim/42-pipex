/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pipex.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: esalim <esalim@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/12/24 16:02:29 by esalim			#+#	#+#			 */
/*   Updated: 2023/01/21 12:24:48 by esalim		   ###   ########.fr	   */
/*																			*/
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
		ft_printf("pipex: %s: No such file or directory\n", av[1]);
		free_paths(commands);
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (access(av[1], R_OK) == -1 || fd == -1)
	{
		ft_printf("pipex: %s: permission denied\n", av[1]);
		free_paths(commands);
		exit(126);
	}
	dup2(fd, STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	if (execve(commands[0], commands, ev) != -1)
	{
		ft_printf("pipex: execve fiald\n");
		free_paths(commands);
		exit(1);
	}
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
	{
		ft_printf("pipex: open fiald\n", av[4]);
		exit(1);
	}
	dup2(pfd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	path = get_path(&commands);
	if (execve(path, commands, ev) != -1)
	{
		ft_printf("pipex: execve fiald\n");
		free_paths(commands);
		exit(1);
	}
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
