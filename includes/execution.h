/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:30:06 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 20:05:40 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "pipex.h"

typedef struct s_fds
{
	int	fd1[2];
	int	fd2[2];
}	t_fds;

int		child_execution(int i, t_data *ptr_data, char **env, t_fds fds);
int		middle_pipe(t_data *ptr_data, t_fds fds);
int		last_pipe(t_data *ptr_data, t_fds fds);
int		first_pipe(t_data *ptr_data, t_fds fds);
int		one_pipe(t_data *ptr_data, t_fds fds);
int		execution(t_data *ptr_data, char **env);
void	swap_fds(t_fds *ptr_fds);
void	close_end(t_fds fds);
void	wait_childs(void);

#endif
