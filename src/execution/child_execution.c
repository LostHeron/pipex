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
#include <stdio.h>
#include <unistd.h>
#include "ft_io.h"

static int	find_commands(int i, t_data *ptr_data, char **env, char **cmd_path);

int	child_execution(int i, t_data *ptr_data, char **env, int (*fds)[2])
{
	int		ret;
	char	*cmd_path;

	if (i == 0 && i == ptr_data->nb_cmds - 1)
	{
		dprintf(2, "case 1\n");
		for (int k = 0; k < ptr_data->nb_cmds - 1 - 1; k++)
		{
			close(fds[k][0]);
			close(fds[k][1]);
		}
		if (dup2(ptr_data->fd_infile, 0) == -1)
			return (ERROR_DUP2);
		if (dup2(ptr_data->fd_outfile, 1) == -1)
			return (ERROR_DUP2);
		close(ptr_data->fd_infile);
		close(ptr_data->fd_outfile);
	}
	else if (i == 0)
	{
		dprintf(2, "case 2\n");
		close(ptr_data->fd_outfile);
		for (int k = 1; k < ptr_data->nb_cmds - 1; k++)
		{
			close(fds[k][0]);
			close(fds[k][1]);
		}
		close(fds[i][0]);
		if (dup2(ptr_data->fd_infile, 0) == -1)
			return (ERROR_DUP2);
		if (dup2(fds[i][1] , 1) == -1)
			return (ERROR_DUP2);
		close(ptr_data->fd_infile);
		close(fds[i][1]);
	}
	else if (i == ptr_data->nb_cmds - 1)
	{
		dprintf(2, "case 3\n");
		close(ptr_data->fd_infile);
		for (int k = 0; k < ptr_data->nb_cmds - 1 - 1; k++)
		{
			close(fds[k][0]);
			close(fds[k][1]);
		}
		close(fds[i - 1][1]);
		if (dup2(fds[i - 1][0] , 0) == -1)
			return (ERROR_DUP2);
		if (dup2(ptr_data->fd_outfile, 1) == -1)
			return (ERROR_DUP2);
		close(fds[i - 1][0]);
		close(ptr_data->fd_outfile);
	}
	else
	{
		dprintf(2, "case 4\n");
		close(ptr_data->fd_infile);
		close(ptr_data->fd_outfile);
		for (int k = 0; k < ptr_data->nb_cmds; k++)
		{
			if (k != i - 1 && k != i)
			{
				close(fds[k][0]);
				close(fds[k][1]);
			}
		}
		close(fds[i - 1][1]);
		close(fds[i][0]);
		if (dup2(fds[i - 1][0], 0) == -1)
			return (ERROR_DUP2);
		if (dup2(fds[i][1], 1) == -1)
			return (ERROR_DUP2);
		close(fds[i - 1][0]);
		close(fds[i][1]);
	}
	ret = find_commands(i, ptr_data, env, &cmd_path);
	if (ret != 0)
		return (ret);
	dprintf(2, "child with id : %i, command found is : '%s'\n", getpid(), cmd_path);
	execve(cmd_path, ptr_data->cmds[i], env);
	return (0);
}

static int	find_commands(int i, t_data *ptr_data, char **env, char **p_cmd_path)
{
	int		j;
	char	*tmp_add_slash;
	(void) env;

	j = 0;
	dprintf(2, "ptr_data->cmds[i][0] = '%s' && i = %i\n", ptr_data->cmds[i][0], i);
	while (ptr_data->paths[j] != 0)
	{
		tmp_add_slash = ft_strjoin(ptr_data->paths[j], "/"); 
		if (tmp_add_slash == NULL)
			return (ERROR_MALLOC);
		*p_cmd_path = ft_strjoin(tmp_add_slash, ptr_data->cmds[i][0]);
		free(tmp_add_slash);
		if (*p_cmd_path == NULL)
			return (ERROR_MALLOC);
		if (access(*p_cmd_path, X_OK) == 0)
			return (0);
		free(*p_cmd_path);
		j++;
	}
	if (access(ptr_data->cmds[i][0], X_OK))
	{
		*p_cmd_path = ft_strdup(ptr_data->cmds[i][0]);
		if (*p_cmd_path == NULL)
			return (ERROR_MALLOC);
		return (0);
	}
	return (1);
}
