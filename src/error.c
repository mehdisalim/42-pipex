/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:37:35 by esalim            #+#    #+#             */
/*   Updated: 2023/01/18 18:56:27 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
/*
void	ft_perror(char	*msg)
{
	perror("Error:");
	exit(1);
}
*/
void	exit_with_error(char *message, int errn)
{
	write(2, message, ft_strlen(message));
	exit(errn);
}

