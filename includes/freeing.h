/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:09:07 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 15:08:04 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREEING_H
# define FREEING_H

# include "pipex.h"
# include "execution.h"

void	free_paths(char **paths);
void	free_cmds(char ***cmds);
void	free_data(t_data data);
int		close_all(t_data *ptr_data, t_fds fds);

#endif
