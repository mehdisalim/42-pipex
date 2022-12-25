/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:30:32 by esalim            #+#    #+#             */
/*   Updated: 2022/12/25 18:08:34 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	perror("Error");
	exit(1);
}

char	**split_commands(char *cmds)
{
	char	**commands;
	char	*cmd_path;

	commands = ft_split(cmds, ' ');
	cmd_path = get_cmd_path(commands[0]);
	free(commands[0]);
	commands[0] = ft_strdup(cmd_path);
	free(cmd_path);
	return (commands);
}
