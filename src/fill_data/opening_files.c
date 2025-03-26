/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:02:23 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 20:23:54 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "pipex.h"

void	opening_files(t_data *ptr_data, char *infile, char *outfile)
{
	ptr_data->fd_infile = open(infile, O_RDONLY);
	if (ptr_data->fd_infile == -1)
		perror(infile);
	if (ptr_data->nb_cmds == 1 && ptr_data->fd_infile == -1)
		return ;
	else
	{
		ptr_data->fd_outfile = open(outfile,
				O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (ptr_data->fd_outfile == -1)
			perror(outfile);
	}
	return ;
}
