/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:30:04 by esalim            #+#    #+#             */
/*   Updated: 2023/01/21 14:59:31 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_env_path(char **env)
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

static char	*remove_end_space(char *cmd)
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

static char	*get_cmd_path(char	*cmd, char **env)
{
	char	*command_path;
	int		i;
	char	**paths;
	char	*tmp;
	char	*str;

	if (ft_strchr(cmd, '/') != 0)
	{
		if (access(cmd, F_OK & X_OK & R_OK) != -1)
			return (cmd);
		ft_printf("pipex: %s: permission denied\n", cmd);
		free(cmd);
		exit(126);
	}
	paths = get_env_path(env);
	i = 0;
	str = remove_end_space(cmd);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command_path = ft_strjoin(tmp, str);
		free(tmp);
		if (access(command_path, F_OK | X_OK) != -1)
		{
			free_paths(paths);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	return (0);
}

static char	get_separator(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i - 1] && cmd[i - 1] == ' ' && cmd[i] == 34)
			return (34);
		if (cmd[i - 1] && cmd[i - 1] == ' ' && cmd[i] == 39)
			return (39);
		i++;
	}
	return (' ');
}

char	**split_commands(char *cmds, char **env)
{
	char	**commands;
	char	*cmd_path;
	char	sep;

	sep = get_separator(cmds);
	commands = ft_split(cmds, sep);
	cmd_path = get_cmd_path(commands[0], env);
	if (!cmd_path)
	{
		ft_printf("pipex: %s: command not found\n", commands[0]);
		free_paths(commands);
		exit(127);
	}
	free(commands[0]);
	commands[0] = ft_strdup(cmd_path);
	free(cmd_path);
	return (commands);
}
