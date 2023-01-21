/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:42:23 by esalim            #+#    #+#             */
/*   Updated: 2023/01/21 12:45:02 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"

void	pipex(char	**av, char *ev[]);
char	*get_cmd_path(char	*cmd, char *env[]);
char	**split_commands(char *cmd, char *env[]);
void    free_paths(char **paths);

#endif
