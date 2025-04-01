/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:50:50 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 20:08:07 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "execution.h"
#include "freeing.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	create_process(int i, t_data *ptr_data, int *p_pid, t_fds *ptr_fds);
static void	child_and_failure(int i, t_data *ptr_data, char **env, t_fds fds);
static void	create_fork(int i, t_data *ptr_data, t_fds *ptr_fds, int *p_pid);

int	execution(t_data *ptr_data, char **env)
{
	t_fds	fds;
	int		pid;
	int		i;

	pid = 1;
	i = 0;
	if (pipe(fds.fd1) == -1)
	{
		free_data(*ptr_data);
		exit(ERROR_PIPE);
	}
	while (i < ptr_data->nb_cmds)
	{
		if (pid != 0)
			create_process(i, ptr_data, &pid, &fds);
		if (pid == 0)
			child_and_failure(i, ptr_data, env, fds);
		else
			swap_fds(&fds);
		i++;
	}
	close_end(fds);
	return (wait_childs(pid, ptr_data->fd_outfile));
}

static void	child_and_failure(int i, t_data *ptr_data, char **env, t_fds fds)
{
	int	ret;

	ret = child_execution(i, ptr_data, env, fds);
	free_cmds(ptr_data->cmds);
	free_paths(ptr_data->paths);
	exit(ret);
}

static void	create_process(int i, t_data *ptr_data, int *p_pid, t_fds *ptr_fds)
{
	if (pipe(ptr_fds->fd2) == -1)
	{
		perror("pipe(ptr_fds->fd2)");
		if (close(ptr_fds->fd1[0]) == -1)
			perror("close(ptr_fds->fd1[0])");
		if (close(ptr_fds->fd1[1]) == -1)
			perror("close(ptr_fds->fd1[1])");
		free_data(*ptr_data);
		exit(ERROR_PIPE);
	}
	create_fork(i, ptr_data, ptr_fds, p_pid);
}

static void	create_fork(int i, t_data *ptr_data, t_fds *ptr_fds, int *p_pid)
{
	if (((i == 0 && ptr_data->fd_infile == -1)
			|| (i == ptr_data->nb_cmds - 1 && ptr_data->fd_outfile == -1)))
		*p_pid = 1;
	else
	{
		*p_pid = fork();
		if (*p_pid == -1)
		{
			perror("fork():");
			if (close(ptr_fds->fd1[0]) == -1)
				perror("close(ptr_fds->fd1[0])");
			if (close(ptr_fds->fd1[1]) == -1)
				perror("close(ptr_fds->fd1[1])");
			free_data(*ptr_data);
			exit(ERROR_FORK);
		}
	}
}
