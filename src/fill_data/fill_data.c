/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:55:56 by jweber            #+#    #+#             */
/*   Updated: 2025/03/18 17:00:58 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "fill_data.h"
#include "ft_io.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

static int	my_return(t_data *ptr_data, int ret);

int	fill_data(t_data *ptr_data, int argc, char **argv, char **env)
{
	int	ret;

	ret = opening_files(ptr_data, argv[1], argv[argc -1]);
	if (ret != 0)
		return (my_return(ptr_data, ret));
	ret = fill_cmds(ptr_data, argc, argv);
	if (ret != 0)
	{
		// SHOULD CLEAR STUFF HERE
		return (my_return(ptr_data, ret));
	}
	ret = fill_paths(ptr_data, env);
	if (ret != 0)
	{
		// SHOULD CLEAR STUFF HERE
		return (my_return(ptr_data, ret));
	}
	return (0);
}

static int	my_return(t_data *ptr_data, int ret)
{
	close(ptr_data->fd_outfile);
	close(ptr_data->fd_infile);
	ft_printf_fd(1, "%s\n", strerror(errno));
	return (ret);
}
