/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:06:56 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 20:20:20 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "freeing.h"
#include <unistd.h>
#include <stdio.h>

void	free_data(t_data data)
{
	if (data.fd_infile != -1)
		if (close(data.fd_infile) == -1)
			perror("close(data.fd_infile)");
	if (data.fd_outfile != -1)
		if (close(data.fd_outfile) == -1)
			perror("close(data.fd_outfile)");
	free_paths(data.paths);
	free_cmds(data.cmds);
}
