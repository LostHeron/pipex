/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:00:46 by jweber            #+#    #+#             */
/*   Updated: 2025/03/18 15:58:17 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <ft_standard.h>
#define WHITE_SPACE " \t\n\v\f\r"

static void	free_all(char ***cmds);

int	fill_cmds(t_data *ptr_data, int argc, char **argv)
{
	int	i;

	ptr_data->nb_cmds = argc - 3;
	ptr_data->cmds = ft_calloc((ptr_data->nb_cmds + 1), sizeof(char **));
	if (ptr_data->cmds == NULL)
		return (ERROR_MALLOC);
	ptr_data->cmds[ptr_data->nb_cmds] = NULL;
	i = 0;
	while (i < ptr_data->nb_cmds)
	{
		ptr_data->cmds[i] = ft_split(argv[2], WHITE_SPACE);
		if (ptr_data->cmds[i] == NULL)
		{
			free_all(ptr_data->cmds);
			ptr_data->cmds = NULL;
			return (ERROR_MALLOC);
		}
		i++;
	}
	return (0);
}

static void	free_all(char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i] != NULL)
	{
		j = 0;
		while (cmds[i][j] != NULL)
		{
			free(cmds[i][j]);
			j++;
		}
		i++;
		free(cmds[i]);
	}
	free(cmds);
}
