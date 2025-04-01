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
#include <stdio.h>
#include <unistd.h>

static int	find_commands(int i, t_data *ptr_data, char **p_cmd_path);
static int	try_raw_cmd(int i, t_data *ptr_data, char **p_cmd_path);
static int	ret_and_free(char *cmd_path, int ret);

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
			printerr_and_ret(ptr_data, cmd_path);
		else
			return (ret_and_free(cmd_path, ret));
	}
	execve(cmd_path, ptr_data->cmds[i], env);
	perror(cmd_path);
	free(cmd_path);
	return (0);
}

static int	cmd_not_empty(int i, t_data *ptr_data, char **p_cmd_path);

static int	find_commands(int i, t_data *ptr_data, char **p_cmd_path)
{
	if (ptr_data->cmds[i][0] != NULL)
	{
		return (cmd_not_empty(i, ptr_data, p_cmd_path));
	}
	else
	{
		*p_cmd_path = ft_strdup("");
		if (*p_cmd_path == NULL)
			return (ERROR_MALLOC);
		return (1);
	}
}

int	cmd_not_empty(int i, t_data *ptr_data, char **p_cmd_path)
{
	int	path_i;
	int	ret;

	ret = 1;
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
		if (access(*p_cmd_path, F_OK) == 0)
			return (0);
		free(*p_cmd_path);
		path_i++;
	}
	ret = try_raw_cmd(i, ptr_data, p_cmd_path);
	return (ret);
}

int	try_raw_cmd(int i, t_data *ptr_data, char **p_cmd_path)
{
	*p_cmd_path = ft_strdup(ptr_data->cmds[i][0]);
	if (*p_cmd_path == NULL)
		return (ERROR_MALLOC);
	if (access(ptr_data->cmds[i][0], X_OK) == 0)
		return (0);
	else
		return (1);
}

static int	ret_and_free(char *cmd_path, int ret)
{
	free(cmd_path);
	return (ret);
}
