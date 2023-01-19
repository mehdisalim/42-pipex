/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:30:32 by esalim            #+#    #+#             */
/*   Updated: 2023/01/19 17:49:56 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**get_env_path(char *env[])
{
	char	**paths;
	int		i;
	char	*path;

	i = -1;
	while (env[++i])
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		if (path)
			break ;
	}
	if (!path)
		return (ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", ':'));
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
		if (s[i] == ' ' || s[i] == '\t')
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

char	*get_cmd_path(char	*cmd, char *env[])
{
	char	*command_path;
	int		i;
	char	**paths;
	char	*tmp;

	if (ft_strnstr(cmd, "./", ft_strlen(cmd)) != 0 || ft_strnstr(cmd, "/bin", ft_strlen(cmd)) != 0)
    {
		if (access(cmd, F_OK | X_OK) != -1)
	    	return (cmd);
		ft_printf("pipex: %s: permission denied\n", cmd);
	  	exit(126);
    }
	paths = get_env_path(env);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command_path, F_OK | X_OK) != -1)
			return (command_path);
		free(command_path);
		i++;
	}
	ft_printf("pipex: %s: Command not found\n", ft_strrchr(cmd, '/'));
	exit(127);
	return (0);
}

char	**split_commands(char *cmds, char *env[])
{
	char	**commands;
	char	*cmd_path;
    char    *tmp;

    if (ft_strchr(cmds, 34))
    {
        commands = ft_split(cmds, 34);
        tmp = ft_strtrim(commands[0], " ");
        free(commands[0]);
        commands[0] = tmp;
        free(tmp);
    }
    else if (ft_strchr(cmds, 39))
    {
        commands = ft_split(cmds, 39);
        tmp = ft_strtrim(commands[0], " ");
        free(commands[0]);
        commands[0] = tmp;
        free(tmp);
    }
//    else
//        commands = sep_cmd(cmds);
    else
        commands = ft_split(cmds, ' ');
	cmd_path = get_cmd_path(commands[0], env);
    ft_printf("\n|%s|\n", cmd_path);
	free(commands[0]);
	commands[0] = ft_strdup(cmd_path);
	free(cmd_path);
	return (commands);
}
