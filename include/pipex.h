/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:42:23 by esalim            #+#    #+#             */
/*   Updated: 2022/12/28 18:29:59 by esalim           ###   ########.fr       */
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
void	exit_with_error(char *message, int errn);

#endif
