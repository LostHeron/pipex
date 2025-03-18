/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:33:37 by jweber            #+#    #+#             */
/*   Updated: 2025/03/18 18:34:20 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_string.h"
#include "pipex.h"
#include "ft_io.h"

static int	find_commands(int i, t_data *ptr_data, char **env, char **cmd_path);

int	child_execution(int i, t_data *ptr_data, char **env)
{
	int		ret;
	char	*cmd_path;

	ft_printf_fd(1, "in child\n");
	if (i == 0)
	{
		/*
		if (dup2(ptr_data->infile, 0) == -1)
			return (ERROR_DUP2);
		if (dup2(fd2[1] , 1) == -1)
			return (ERROR_DUP2);
			*/
		;;
	}
	else if (i == ptr_data->nb_cmds - 1)
	{
		;;
	}
	else
	{
		/*
		dup2(fd1[0], 0);
		*/
		;;
	}
	ret = find_commands(i, ptr_data, env, &cmd_path);
	if (ret != 0)
		return (ret);
	ft_printf_fd(1, "command found is : '%s'\n", cmd_path);
	//execve(cmd_path, data_ptr->cmds, env);
	return (0);
}

static int	find_commands(int i, t_data *ptr_data, char **env, char **p_cmd_path)
{
	int		j;
	int		len;
	(void) env;

	ft_printf_fd(1, "in find_commands\n");
	j = 0;
	while (ptr_data->paths[j] != 0)
	{
		len = ft_strlen(ptr_data->paths[j]);
		if (ptr_data->paths[j][len - 1] != '/')
			add_slash;
		*p_cmd_path = ft_strjoin(ptr_data->paths[i], ptr_data->cmds[i][0]);
		ft_printf_fd(1, "*p_cmd_path = '%s'\n", *p_cmd_path);
		if (access(*p_cmd_path, X_OK) == 0)
			return (0);
		free(*p_cmd_path);
		j++;
	}
	return (1);
}
