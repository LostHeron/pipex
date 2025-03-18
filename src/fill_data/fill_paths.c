/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:50:47 by jweber            #+#    #+#             */
/*   Updated: 2025/03/18 16:38:44 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "pipex.h"
#include "ft_io.h"
#include "ft_standard.h"

int	fill_paths(t_data *ptr_data, char **env)
{
	int	i;

	i = 0;
	ptr_data->paths = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			ptr_data->paths = ft_split(env[i] + 5, ":");
			if (ptr_data->paths == NULL)
				return (ERROR_MALLOC);
			else
				return (0);
		}
		i++;
	}
	// add a '/' to the end of each command if there is none !
	return (0);
}
