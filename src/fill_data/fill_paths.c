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
#include "ft_standard.h"

static int	add_slash_path(t_data *ptr_data);

int	fill_paths(t_data *ptr_data, char **env)
{
	int	i;
	int	ret;

	i = 0;
	ptr_data->paths = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			ptr_data->paths = ft_split(env[i] + 5, ":");
			if (ptr_data->paths == NULL)
				return (ERROR_MALLOC);
			ret = add_slash_path(ptr_data);
			if (ret != 0)
				return (ret);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

static int	add_slash_path(t_data *ptr_data)
{
	int		i;
	int		len;
	char	*tmp_path;

	i = 0;
	while (ptr_data->paths[i] != NULL)
	{
		len = ft_strlen(ptr_data->paths[i]);
		tmp_path = ft_malloc((len + 2) * sizeof(char));
		if (tmp_path == NULL)
			return (1);
		ft_strcpy(tmp_path, ptr_data->paths[i]);
		tmp_path[len] = '/';
		tmp_path[len + 1] = '\0';
		free(ptr_data->paths[i]);
		ptr_data->paths[i] = tmp_path;
		i++;
	}
	return (0);
}
