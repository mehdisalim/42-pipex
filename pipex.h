/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:42:23 by esalim            #+#    #+#             */
/*   Updated: 2023/01/21 17:05:56 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

void	pipex(char	**av, char *ev[]);
char	**split_commands(char *cmd, char *env[]);
void	free_paths(char **paths);
char	**get_env_path(char **env);
char	*remove_end_space(char *cmd);
void	ft_exit(char *message, char *filename, char **commands, int errno);

#endif
