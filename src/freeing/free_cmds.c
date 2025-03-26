/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:19:38 by jweber            #+#    #+#             */
/*   Updated: 2025/03/26 13:19:51 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_cmds(char ***cmds)
{
	int	i;
	int	j;

	if (cmds != NULL)
	{
		i = 0;
		while (cmds[i] != NULL)
		{
			j = 0;
			while (cmds[i][j] != NULL)
			{
				free(cmds[i][j]);
				j++;
			}
			free(cmds[i]);
			i++;
		}
		free(cmds);
	}
}
