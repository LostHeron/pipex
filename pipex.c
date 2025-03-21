/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:12:57 by jweber            #+#    #+#             */
/*   Updated: 2025/03/18 15:57:08 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "execution.h"
#include "ft_io.h"
#include "pipex.h"
#include "fill_data.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		ret;

	if (argc < 5)
	{
		ft_printf_fd(1, "wrong number of arguments\n");
		ft_printf_fd(1, "usage : ./pipex arg1 arg2 arg3 arg4");
		return (1);
	}
	ret = fill_data(&data, argc, argv, env);
	if (ret != 0)
		return (0);
	ret = execution(&data, env);
	return (0);
}

/*
int	realise_pipe(t_data *ptr_data)
{
	int	pid;

	pid = 1;
	for (int i = 0; i < 2; i++)
	{
		if (pid != 1)
		{
			pid = fork();

			if (pid == -1)
			{
				ft_printf_fd(1, "%s\n", strerror(errno));
				return (3);
			}
			else
			{
				ft_printf_fd(1, "process sucessfully created\n");
			}
		}
		if (pid == 0)
		{
			// in child exec
			execve(
		}
		else
		{
			// in parent after chile exec
		}
	}
}
*/
