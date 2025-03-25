/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:50:50 by jweber            #+#    #+#             */
/*   Updated: 2025/03/25 21:59:48 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "execution.h"
#include "ft_io.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	execution(t_data *ptr_data, char **env)
{
	t_fds	fds;
	int		pid;
	int		i;
	int		ret;
	int		wait_id;

	pid = 1;
	i = 0;
	if (pipe(fds.fd1) == -1)
		return (ERROR_PIPE);
	while (i < ptr_data->nb_cmds)
	{
		if (pid != 0)
		{
			if (pipe(fds.fd2) == -1)
				return (ERROR_PIPE);
			pid = fork();
			if (pid == -1)
				return (ERROR_FORK);
		}
		if (pid == 0)
		{
			ret = child_execution(i, ptr_data, env, fds);
			/*
			if (ret != 0)
			{
				// should clear stuff here !
				exit (ret);
			}
			*/
			exit(ret);
		}
		else
		{
			close(fds.fd1[0]);
			close(fds.fd1[1]);
			fds.fd1[0] = fds.fd2[0];
			fds.fd1[1] = fds.fd2[1];
		}
		i++;
	}
	close(fds.fd1[0]);
	close(fds.fd1[1]);
	close(ptr_data->fd_infile);
	close(ptr_data->fd_outfile);
	wait_id = 1;
	while (wait_id != -1)
		wait_id = wait(NULL);
	return (0);
}
