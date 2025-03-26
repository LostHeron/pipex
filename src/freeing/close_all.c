/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:06:38 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 15:22:43 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "execution.h"
#include "ft_io.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

static void	close_fds(t_fds fds, int *ret);

int	close_all(t_data *ptr_data, t_fds fds)
{
	int	ret;

	ret = 0;
	close_fds(fds, &ret);
	if (close(ptr_data->fd_infile) == -1)
	{
		ft_printf_fd(2, "%s\n", strerror(errno));
		ret += 16;
	}
	if (close(ptr_data->fd_outfile) == -1)
	{
		ft_printf_fd(2, "%s\n", strerror(errno));
		ret += 32;
	}
	return (ret);
}

static void	close_fds(t_fds fds, int *ret)
{
	if (close(fds.fd1[0]) == -1)
	{
		ft_printf_fd(2, "%s\n", strerror(errno));
		*ret += 1;
	}
	if (close(fds.fd1[1]) == -1)
	{
		ft_printf_fd(2, "%s\n", strerror(errno));
		*ret += 2;
	}
	if (close(fds.fd2[0]) == -1)
	{
		ft_printf_fd(2, "%s\n", strerror(errno));
		*ret += 4;
	}
	if (close(fds.fd2[1]) == -1)
	{
		ft_printf_fd(2, "%s\n", strerror(errno));
		*ret += 8;
	}
}
