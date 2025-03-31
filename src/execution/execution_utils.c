/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:30:00 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 20:05:05 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "execution.h"
#include "ft_io.h"
#include <unistd.h>
#include <sys/wait.h>

void	swap_fds(t_fds *ptr_fds)
{
	if (close(ptr_fds->fd1[0]) == -1)
		perror("close(ptr_fds->fd1[0])");
	if (close(ptr_fds->fd1[1]) == -1)
		perror("close(ptr_fds->fd1[1])");
	ptr_fds->fd1[0] = ptr_fds->fd2[0];
	ptr_fds->fd1[1] = ptr_fds->fd2[1];
}

void	close_end(t_fds fds)
{
	if (close(fds.fd1[0]) == -1)
		perror("close(fds.fd1[0]))");
	if (close(fds.fd1[1]) == -1)
		perror("close(fds.fd1[1]))");
}

int	wait_childs(int pid, int fd_outfile)
{
	int	wait_id;
	int	status;
	int	ret;

	wait_id = 1;
	while (wait_id != -1)
	{
		wait_id = wait(&status);
		if (wait_id == pid)
		{
			if (WIFEXITED(status) != 0)
				ret = WEXITSTATUS(status);
			else if (WIFSIGNALED(status) != 0)
				ret = WTERMSIG(status) + 128;
			else
				ft_printf_fd(2, "child was not terminated normally\n");
		}
	}
	if (fd_outfile == -1)
		return (1);
	return (ret);
}
