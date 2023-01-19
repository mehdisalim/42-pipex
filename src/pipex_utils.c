/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:30:32 by esalim            #+#    #+#             */
/*   Updated: 2023/01/19 22:53:48 by esalim           ###   ########.fr       */
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

char	**split_commands(char *command, char *env[])
{
	char	**commands;
	char	*cmd_path;
    char    *cmds = ft_strdup(command);
    int i = 0;

    while (cmds[i])
    {
        if (cmds[i] == 34 && cmds[i + 1] && cmds[i + 1] == 39)
            cmds[i] = 39;
        else if (cmds[i] == 39 && cmds[i + 1] && cmds[i + 1] == 34)
            cmds[i] = 34;
       i++; 
    }
    if (ft_strchr(cmds, 34))
        commands = ft_split(cmds, 34);
    else if (ft_strchr(cmds, 39))
        commands = ft_split(cmds, 39);
    else
        commands = ft_split(cmds, ' ');
    ft_printf("#%s#\n", commands[0]);
    ft_printf("#%s#\n", commands[1]);
    ft_printf("#%s#\n", commands[2]);
	cmd_path = get_cmd_path(commands[0], env);
    if (!cmd_path)
    {
	    ft_printf("pipex: %s: Command not found\n", commands[0]);
        exit(126);
    }
    //ft_printf("\n|%s|\n", cmd_path);
	free(commands[0]);
	commands[0] = ft_strdup(cmd_path);
	free(cmd_path);
	return (commands);
}
