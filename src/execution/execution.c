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
#include <unistd.h>
#include <stdlib.h>

int	execution(t_data *ptr_data, char **env)
{
	int	fd1[2];
	(void) fd1;
	int	fd2[2];
	int	pid;
	int	i;
	int	ret;

	pid = 1;
	i = 0;
	while (i < ptr_data->nb_cmds)
	{
		if (pid != 0)
		{
			if (pipe(fd2) == -1)
				return (ERROR_PIPE);
			pid = fork();
			if (pid == -1)
				return (ERROR_FORK);
			if (pid != 0)
				ft_printf_fd(1, "fork succesfully created !\n");
		}
		if (pid == 0)
		{
			ret = child_execution(i, ptr_data, env);
			/*
			if (ret != 0)
			{
				// should clear stuff here !
				return (ret);
			}
			*/
			exit(0);
		}
		else
		{
			/*
			close(fd1[0]);
			close(fd1[1]);
			fd1[0] = fd2[0];
			fd1[1] = fd2[1];
			*/
		}
		i++;
	}
	return (0);
}
