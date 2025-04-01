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

#include <stdlib.h>
#include "execution.h"
#include "freeing.h"
#include "ft_io.h"
#include "fill_data.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		ret;

	if (argc != 5)
	{
		ft_printf_fd(2, "wrong number of arguments\n");
		ft_printf_fd(2, "usage : ./pipex arg1 arg2 arg3 arg4\n");
		return (1);
	}
	data.paths = NULL;
	data.cmds = NULL;
	ret = fill_data(&data, argc, argv, env);
	if (ret != 0)
		return (ret);
	ret = execution(&data, env);
	free_data(data);
	return (ret);
}
