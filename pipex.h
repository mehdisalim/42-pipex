/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:42:23 by esalim            #+#    #+#             */
/*   Updated: 2023/01/21 15:01:57 by esalim           ###   ########.fr       */
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

#endif
