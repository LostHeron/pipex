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

#include "pipex.h"
#include "execution.h"
#include "ft_io.h"
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

void	swap_fds(t_fds *ptr_fds)
{
	close(ptr_fds->fd1[0]);
	close(ptr_fds->fd1[1]);
	ptr_fds->fd1[0] = ptr_fds->fd2[0];
	ptr_fds->fd1[1] = ptr_fds->fd2[1];
}

void	close_end(t_fds fds)
{
	if (close(fds.fd1[0]) == -1)
		ft_printf_fd(2, "errno: %s\n", strerror(errno));
	if (close(fds.fd1[1]) == -1)
		ft_printf_fd(2, "errno: %s\n", strerror(errno));
}

void	wait_childs(void)
{
	int	wait_id;

	wait_id = 1;
	while (wait_id != -1)
		wait_id = wait(NULL);
}
