/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:00:40 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 15:09:40 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "freeing.h"
#include "ft_io.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	one_pipe(t_data *ptr_data, t_fds fds)
{
	int	ret;

	if (ptr_data->fd_infile != -1 && ptr_data->fd_outfile != -1)
	{
		ret = 0;
		if (dup2(ptr_data->fd_infile, 0) == -1)
		{
			perror("dup2(ptr_data->fd_infile, 0)");
			ret = ERROR_DUP2;
		}
		if (dup2(ptr_data->fd_outfile, 1) == -1)
		{
			perror("dup2(ptr_data->fd_infile, 0)");
			ret = ERROR_DUP2;
		}
		close_all(ptr_data, fds);
		return (ret);
	}
	else
	{
		close_all(ptr_data, fds);
		free_data(*ptr_data);
		exit(0);
	}
}

int	first_pipe(t_data *ptr_data, t_fds fds)
{
	int	ret;

	if (ptr_data->fd_infile != -1)
	{
		ret = 0;
		if (dup2(ptr_data->fd_infile, 0) == -1)
		{
			perror("dup2(ptr_data->fd_infile, 0)");
			ret = ERROR_DUP2;
		}
		if (dup2(fds.fd2[1], 1) == -1)
		{
			perror("dup2(fds.fd2[1], 1)");
			ret = ERROR_DUP2;
		}
		close_all(ptr_data, fds);
		return (ret);
	}
	else
	{
		close_all(ptr_data, fds);
		free_data(*ptr_data);
		exit(0);
	}
}

int	last_pipe(t_data *ptr_data, t_fds fds)
{
	int	ret;

	if (ptr_data->fd_outfile != -1)
	{
		ret = 0;
		if (dup2(fds.fd1[0], 0) == -1)
		{
			perror("dup2(fds.fd1[0], 0)");
			ret = ERROR_DUP2;
		}
		if (dup2(ptr_data->fd_outfile, 1) == -1)
		{
			perror("dup2(ptr_data->fd_outfile, 1)");
			ret = ERROR_DUP2;
		}
		close_all(ptr_data, fds);
		return (ret);
	}
	else
	{
		close_all(ptr_data, fds);
		free_data(*ptr_data);
		exit(0);
	}
}

int	middle_pipe(t_data *ptr_data, t_fds fds)
{
	int	ret;

	ret = 0;
	if (dup2(fds.fd1[0], 0) == -1)
	{
		perror("dup2(fds.fd1[0], 0)");
		ret = ERROR_DUP2;
	}
	if (dup2(fds.fd2[1], 1) == -1)
	{
		perror("dup2(fds.fd2[1], 1)");
		ret = ERROR_DUP2;
	}
	close_all(ptr_data, fds);
	return (ret);
}

int	printerr_and_ret(t_data *ptr_data, char *cmd_path)
{
	ft_printf_fd(2, "%s: command not found\n", cmd_path);
	free_cmds(ptr_data->cmds);
	free_paths(ptr_data->paths);
	free(cmd_path);
	exit(127);
}
