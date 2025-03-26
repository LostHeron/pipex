/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:10:52 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 13:40:31 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILL_DATA_H
# define FILL_DATA_H

# include "pipex.h"

void	opening_files(t_data *ptr_data, char *infile, char *outfile);
int		fill_cmds(t_data *data, char **argv);
int		fill_paths(t_data *ptr_data, char **env);
int		fill_data(t_data *data, int argc, char **argv, char **env);

#endif
