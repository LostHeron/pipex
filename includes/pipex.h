/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:57:55 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 20:09:59 by jweber           ###   ########.fr       */
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

# define ERROR_WRITE -1
# define ERROR_READ -2
# define ERROR_MALLOC -3
# define ERROR_PIPE -4
# define ERROR_CLOSE -5
# define ERROR_FORK -6
# define ERROR_DUP2 -7

#endif
