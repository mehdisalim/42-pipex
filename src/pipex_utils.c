/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:30:32 by esalim            #+#    #+#             */
/*   Updated: 2022/12/28 17:17:14 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**get_env_path(char **env)
{
	char	**paths;
	int		i;
	char	*path;

	i = -1;
	while (env[++i])
	{
		path = ft_strnstr(env[i], "PATH=", ft_strlen(env[i]));
		if (path)
			break ;
	}
	if (!path)
		exit(1);
	paths = ft_split(path + 5, ':');
	if (!paths)
		exit(1);
	return (paths);
}

char	**sep_cmd(char *s)
{
	char	**cmds;
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(s);
	cmds = malloc(3 * sizeof(char *));
	if (!cmds)
		exit(0);
	while (s[++i])
		if (s[i] == ' ')
			break ;
	cmds[0] = ft_substr(s, 0, i);
	if (i != len)
		cmds[1] = ft_substr(s, i + 1, len);
	else
		cmds[1] = 0;
	if (cmds[1] != 0)
		cmds[2] = 0;
	return (cmds);
}

char	*get_cmd_path(char	*cmd, char **env)
{
	char	*command_path;
	int		i;
	char	**paths;
	char	*tmp;

	if (ft_strnstr(cmd, "bin", ft_strlen(cmd)) != 0)
		return (cmd);
	paths = get_env_path(env);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command_path, X_OK) != -1)
			return (command_path);
		free(command_path);
		i++;
	}
	//perror("Error");
	write(2, "Error:  No such file or directory", 33);
	exit(127);
}

char	**split_commands(char *cmds, char **env)
{
	char	**commands;
	char	*cmd_path;

	commands = sep_cmd(cmds);
	cmd_path = get_cmd_path(commands[0], env);
	free(commands[0]);
	commands[0] = ft_strdup(cmd_path);
	free(cmd_path);
	return (commands);
}
