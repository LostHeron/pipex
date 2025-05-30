/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:06:38 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 20:22:40 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "execution.h"
#include <unistd.h>
#include <stdio.h>

static void	close_fds(t_fds fds, int *ret);

int	close_all(t_data *ptr_data, t_fds fds)
{
	int	ret;

	ret = 0;
	close_fds(fds, &ret);
	if (ptr_data->fd_infile != -1)
	{
		if (close(ptr_data->fd_infile) == -1)
		{
			perror("close(ptr_data->fd_infile)");
			ret += 16;
		}
	}
	if (ptr_data->fd_outfile != -1)
	{
		if (close(ptr_data->fd_outfile) == -1)
		{
			perror("close(ptr_data->fd_outfile)");
			ret += 32;
		}
	}
	return (ret);
}

static void	close_fds(t_fds fds, int *ret)
{
	if (close(fds.fd1[0]) == -1)
	{
		perror("close(fds.fd1[0])");
		*ret += 1;
	}
	if (close(fds.fd1[1]) == -1)
	{
		perror("close(fds.fd1[1])");
		*ret += 2;
	}
	if (close(fds.fd2[0]) == -1)
	{
		perror("close(fds.fd2[0])");
		*ret += 4;
	}
	if (close(fds.fd2[1]) == -1)
	{
		perror("close(fds.fd2[1])");
		*ret += 8;
	}
}
