/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:00:40 by jweber            #+#    #+#             */
/*   Updated: 2025/03/25 21:01:04 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <unistd.h>

int	one_pipe(t_data *ptr_data, t_fds fds)
{
	close(fds.fd1[0]);
	close(fds.fd1[1]);
	close(fds.fd2[0]);
	close(fds.fd2[1]);
	if (dup2(ptr_data->fd_infile, 0) == -1)
		return (ERROR_DUP2);
	if (dup2(ptr_data->fd_outfile, 1) == -1)
		return (ERROR_DUP2);
	close(ptr_data->fd_infile);
	close(ptr_data->fd_outfile);
	return (0);
}

int	first_pipe(t_data *ptr_data, t_fds fds)
{
	close(ptr_data->fd_outfile);
	close(fds.fd1[0]);
	close(fds.fd1[1]);
	close(fds.fd2[0]);
	if (dup2(ptr_data->fd_infile, 0) == -1)
		return (ERROR_DUP2);
	if (dup2(fds.fd2[1], 1) == -1)
		return (ERROR_DUP2);
	close(ptr_data->fd_infile);
	close(fds.fd2[1]);
	return (0);
}

int	last_pipe(t_data *ptr_data, t_fds fds)
{
	close(ptr_data->fd_infile);
	close(fds.fd1[1]);
	close(fds.fd2[0]);
	close(fds.fd2[1]);
	if (dup2(fds.fd1[0], 0) == -1)
		return (ERROR_DUP2);
	if (dup2(ptr_data->fd_outfile, 1) == -1)
		return (ERROR_DUP2);
	close(fds.fd1[0]);
	close(ptr_data->fd_outfile);
	return (0);
}

int	middle_pipe(t_data *ptr_data, t_fds fds)
{
	close(ptr_data->fd_infile);
	close(ptr_data->fd_outfile);
	close(fds.fd1[1]);
	close(fds.fd2[0]);
	if (dup2(fds.fd1[0], 0) == -1)
		return (ERROR_DUP2);
	if (dup2(fds.fd2[1], 1) == -1)
		return (ERROR_DUP2);
	close(fds.fd1[0]);
	close(fds.fd2[1]);
	return (0);
}
