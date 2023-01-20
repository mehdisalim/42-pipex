/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:30:32 by esalim            #+#    #+#             */
/*   Updated: 2023/01/20 19:15:27 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**get_env_path(char **env)
{
	char	**paths;
	int		i;
	char	*path;

	i = -1;
    if (!env)
		return (ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", ':'));
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
/*
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
*/
char    *remove_end_space(char *cmd)
{
    int i = 0;
    while (cmd[i])
    {
        if (cmd[i] == ' ')
            cmd[i] = 0;
        i++;
    }
    return (cmd);
}

char	*get_cmd_path(char	*cmd, char **env)
{
	char	*command_path;
	int		i;
	char	**paths;
	char	*tmp;

	if (ft_strnstr(cmd, "./", ft_strlen(cmd)) != 0 || ft_strnstr(cmd, "/bin", ft_strlen(cmd)) != 0)
    {
		if (access(cmd, F_OK & X_OK & R_OK) != -1)
	    	return (cmd);
		ft_printf("pipex: %s: permission denied\n", cmd);
	  	exit(126);
    }
	paths = get_env_path(env);
	i = 0;
    char    *str = remove_end_space(cmd);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command_path = ft_strjoin(tmp, str);
		free(tmp);
		if (access(command_path, F_OK | X_OK) != -1)
			return (command_path);
		free(command_path);
		i++;
	}
	return (0);
}

char    get_separator(char *cmd)
{
    int i = 0;
    while (cmd[i])
    {
        if (cmd[i] == 34)
            return (34);
        if (cmd[i] == 39)
            return (39);
        i++;
    }
    return (' ');
}

char	**split_commands(char *cmds, char **env)
{
	char	**commands;
	char	*cmd_path;

    /*
    char *squates = ft_strchr(cmds, 34);
    char *dquates = ft_strchr(cmds, 39);
    if (squates && squates[0] == 34 && squates[1] && squates[1] == 39)
    {
        ft_printf("awk: syntax error at source line 1\n context is\n	 >>> ' <<<\nawk: bailing out at source line 1\n");
        exit(2);
    }
    else if (dquates && dquates[0] == 39 && dquates[1] && dquates[1] == 34)
        commands = ft_split(cmds, 39);
    else if (squates && squates[0] == 34 && squates[1] && squates[1] == 39)
        commands = ft_split(cmds, 34);
    else if (ft_strchr(cmds, 39))
        commands = ft_split(cmds, 39);
    else if (ft_strchr(cmds, 34) && !ft_strchr(cmds, 39))
        commands = ft_split(cmds, 34);
    else*/
    char sep = get_separator(cmds);
    commands = ft_split(cmds, sep);
	cmd_path = get_cmd_path(commands[0], env);
    if (!cmd_path)
    {
	    ft_printf("pipex: %s: command not found\n", commands[0]);
        exit(127);
    }
	free(commands[0]);
	commands[0] = ft_strdup(cmd_path);
	free(cmd_path);
	return (commands);
}
