/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:30:32 by esalim            #+#    #+#             */
/*   Updated: 2022/12/27 10:44:27 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

char	*get_cmd_path(char	*cmd)
{
	char	*command_path;
	int		usr_bin;
	int		bin;

	command_path = ft_strjoin("/usr/bin/", cmd);
	usr_bin = access(command_path, F_OK);
	if (usr_bin != -1)
		return (command_path);
	free(command_path);
	command_path = ft_strjoin("/bin/", cmd);
	bin = access(command_path, F_OK);
	if (bin != -1 )
		return (command_path);
	exit(2);
}

char	**split_commands(char *cmds)
{
	char	**commands;
	char	*cmd_path;

	commands = sep_cmd(cmds);
	cmd_path = get_cmd_path(commands[0]);
	free(commands[0]);
	commands[0] = ft_strdup(cmd_path);
	free(cmd_path);
	return (commands);
}
