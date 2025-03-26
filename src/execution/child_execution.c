/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:33:37 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 19:41:01 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_string.h"
#include "execution.h"
#include "pipex.h"
#include "ft_io.h"
#include <stdio.h>
#include <unistd.h>

static int	find_commands(int i, t_data *ptr_data, char **p_cmd_path);
static int	try_raw_cmd(int i, t_data *ptr_data, char **p_cmd_path);

int	child_execution(int i, t_data *ptr_data, char **env, t_fds fds)
{
	int		ret;
	char	*cmd_path;

	if (i == 0 && i == ptr_data->nb_cmds - 1)
		one_pipe(ptr_data, fds);
	else if (i == 0)
		first_pipe(ptr_data, fds);
	else if (i == ptr_data->nb_cmds - 1)
		last_pipe(ptr_data, fds);
	else
		middle_pipe(ptr_data, fds);
	ret = find_commands(i, ptr_data, &cmd_path);
	if (ret != 0)
	{
		if (ret == 1)
		{
			ft_printf_fd(2, "command not found : %s\n", ptr_data->cmds[i][0]);
			return (ret);
		}
		else
			return (ret);
	}
	execve(cmd_path, ptr_data->cmds[i], env);
	free(cmd_path);
	return (0);
}

static int	find_commands(int i, t_data *ptr_data, char **p_cmd_path)
{
	int	path_i;
	int	ret;

	if (ptr_data->cmds[i][0][0] == '/')
	{
		*p_cmd_path = ft_strdup(ptr_data->cmds[i][0]);
		if (*p_cmd_path == NULL)
			return (ERROR_MALLOC);
		return (0);
	}
	path_i = 0;
	while (ptr_data->paths[path_i] != 0)
	{
		*p_cmd_path = ft_strjoin(ptr_data->paths[path_i], ptr_data->cmds[i][0]);
		if (*p_cmd_path == NULL)
			return (ERROR_MALLOC);
		if (access(*p_cmd_path, X_OK) == 0)
			return (0);
		free(*p_cmd_path);
		path_i++;
	}
	ret = try_raw_cmd(i, ptr_data, p_cmd_path);
	if (ret == 0)
		return (0);
	return (1);
}

int	try_raw_cmd(int i, t_data *ptr_data, char **p_cmd_path)
{
	if (access(ptr_data->cmds[i][0], X_OK))
	{
		*p_cmd_path = ft_strdup(ptr_data->cmds[i][0]);
		if (*p_cmd_path == NULL)
			return (ERROR_MALLOC);
		return (0);
	}
	return (1);
}
