/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:57:58 by esalim            #+#    #+#             */
/*   Updated: 2023/01/21 17:10:09 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}

char	**get_env_path(char **env)
{
	char	**paths;
	int		i;
	char	*path;
	char	*default_path;

	i = -1;
	default_path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:./";
	if (!env || !*env)
		return (ft_split(default_path, ':'));
	while (env[++i])
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		if (path)
			break ;
	}
	paths = ft_split(path + 5, ':');
	if (!paths)
		exit(1);
	return (paths);
}

char	*remove_end_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			cmd[i] = 0;
		i++;
	}
	return (cmd);
}

void	ft_exit(char *message, char *filename, char **commands, int errno)
{
	ft_printf("pipex: %s: %s\n", filename, message);
	free_paths(commands);
	exit(errno);
}
