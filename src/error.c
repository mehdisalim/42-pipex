/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:37:35 by esalim            #+#    #+#             */
/*   Updated: 2022/12/28 16:25:20 by esalim           ###   ########.fr       */
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

