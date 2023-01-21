/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_leaks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:40:21 by esalim            #+#    #+#             */
/*   Updated: 2023/01/21 12:54:38 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void    free_paths(char **paths)
{
    int i;

    if (!paths)
        return ;
    i = -1;
    while (paths[++i])
        free(paths[i]);
    free(paths);
}