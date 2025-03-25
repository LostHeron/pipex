/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:06:56 by jweber            #+#    #+#             */
/*   Updated: 2025/03/25 22:11:56 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"

void	free_data(t_data data)
{
	int	i;
	int	j;

	i = 0;
	while (data.paths[i] != NULL)
	{
		free(data.paths[i]);
		i++;
	}
	free(data.paths);
	i = 0;
	while (data.cmds[i] != NULL)
	{
		j = 0;
		while (data.cmds[i][j] != NULL)
		{
			free(data.cmds[i][j]);
			j++;
		}
		free(data.cmds[i]);
		i++;
	}
	free(data.cmds);
}
