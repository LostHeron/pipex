/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:50:50 by jweber            #+#    #+#             */
/*   Updated: 2025/03/18 18:32:49 by jweber           ###   ########.fr       */
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
	int	fd1[2];
	int	fd2[2];
	int	pid;
	int	i;
	int	ret;

	pid = 1;
	i = 0;
	if (pipe(fd1) == -1)
		return (ERROR_PIPE);
	while (i < ptr_data->nb_cmds)
	{
		if (pid != 0)
		{
			if (pipe(fd2) == -1)
				return (ERROR_PIPE);
			pid = fork();
			if (pid == -1)
			{
				dprintf(1, "error while forking\n");
				return (ERROR_FORK);
			}
			if (pid != 0)
				dprintf(2, "fork succesfully created !, child of id %i created\n", pid);
		}
		if (pid == 0)
		{
			ret = child_execution(i, ptr_data, env, fd1, fd2);
			dprintf(2, "ERROR in EXEVE\n");
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
			close(fd1[0]);
			close(fd1[1]);
			fd1[0] = fd2[0];
			fd1[1] = fd2[1];
		}
		i++;
	}
	close(fd1[0]);
	close(fd1[1]);
	close(ptr_data->fd_infile);
	close(ptr_data->fd_outfile);
	int wait_pid;
	while ((wait_pid = waitpid(-1, NULL, WNOHANG)) != -1)
	{
		if (wait_pid == 0)
			printf("waiting for a child\n");
		else
			printf("waited for child with id : %i\n", wait_pid);
		usleep(100000);
	}
	return (0);
}
