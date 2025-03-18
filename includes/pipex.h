/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:57:55 by jweber            #+#    #+#             */
/*   Updated: 2025/03/18 17:20:22 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_data
{
	int		fd_infile;
	int		fd_outfile;
	char	***cmds;
	int		nb_cmds;
	char	**paths;
}	t_data;

typedef enum e_error
{
	ERROR_WRITE = -1,
	ERROR_READ = -2,
	ERROR_MALLOC = -3,
	ERROR_PIPE = -4,
	ERROR_CLOSE = -5,
	ERROR_FORK = -6,
	ERROR_DUP2 = -7,
}	t_error;

#endif
