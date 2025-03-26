/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:12:57 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 19:58:44 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execution.h"
#include "ft_io.h"
#include "pipex.h"
#include "fill_data.h"
#include "freeing.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		ret;

	if (argc < 4) // a remplacer par != 5 pour les non bonus !!
	{
		ft_printf_fd(2, "wrong number of arguments\n");
		ft_printf_fd(2, "usage : ./pipex arg1 arg2 arg3 arg4");
		return (1);
	}
	data.paths = NULL;
	data.cmds = NULL;
	ret = fill_data(&data, argc, argv, env);
	if (ret != 0)
		return (ret);
	ret = execution(&data, env);
	free_data(data);
	return (0);
}
