/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:30:06 by jweber            #+#    #+#             */
/*   Updated: 2025/03/18 18:30:42 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "pipex.h"

int	child_execution(int i, t_data *ptr_data, char **env, int *fd1, int *fd2);
int	execution(t_data *ptr_data, char **env);

#endif
