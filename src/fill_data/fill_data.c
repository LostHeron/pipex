/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:55:56 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 20:24:50 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "fill_data.h"
#include "freeing.h"
#include <stdio.h>
#include <unistd.h>

static int	my_return(t_data *ptr_data, int ret);

int	fill_data(t_data *ptr_data, int argc, char **argv, char **env)
{
	int	ret;

	ptr_data->nb_cmds = argc - 3;
	opening_files(ptr_data, argv[1], argv[argc -1]);
	ret = fill_cmds(ptr_data, argv);
	if (ret != 0)
		return (my_return(ptr_data, ret));
	ret = fill_paths(ptr_data, env);
	if (ret != 0)
	{
		free_cmds(ptr_data->cmds);
		return (my_return(ptr_data, ret));
	}
	return (0);
}

static int	my_return(t_data *ptr_data, int ret)
{
	if (ptr_data->fd_infile != -1)
		if (close(ptr_data->fd_infile) == -1)
			perror("ptr_data->fd_infile");
	if (ptr_data->fd_outfile != -1)
		if (close(ptr_data->fd_outfile) == -1)
			perror("ptr_data->fd_outfile");
	return (ret);
}
