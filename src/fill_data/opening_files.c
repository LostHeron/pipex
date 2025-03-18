/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:02:23 by jweber            #+#    #+#             */
/*   Updated: 2025/03/18 15:03:27 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "pipex.h"

int	opening_files(t_data *ptr_data, char *file1, char *file2)
{
	int	ret;

	ret = 0;
	ptr_data->fd_infile = open(file1, O_RDONLY | O_CREAT, 0666);
	if (ptr_data->fd_infile == -1)
	{
		ret = -1;
	}
	ptr_data->fd_outfile = open(file2, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (ptr_data->fd_outfile == -1)
	{
		ret = -1;
	}
	return (ret);
}
