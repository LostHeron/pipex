/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:00:46 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 13:24:27 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "freeing.h"
#include <ft_standard.h>
#define WHITE_SPACE " \t\n\v\f\r"

int	fill_cmds(t_data *ptr_data, char **argv)
{
	int	i;

	ptr_data->cmds = ft_calloc((ptr_data->nb_cmds + 1), sizeof(char **));
	if (ptr_data->cmds == NULL)
		return (ERROR_MALLOC);
	i = 0;
	while (i < ptr_data->nb_cmds)
	{
		ptr_data->cmds[i] = ft_split(argv[i + 2], WHITE_SPACE);
		if (ptr_data->cmds[i] == NULL)
		{
			free_cmds(ptr_data->cmds);
			ptr_data->cmds = NULL;
			return (ERROR_MALLOC);
		}
		i++;
	}
	return (0);
}
