/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:04:27 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/07 19:46:59 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_vars(t_vars *vars)
{
	vars->case_size = 10.0f;
	vars->time = 0.0f;
	vars->player.aimed_obj = NULL;
	vars->player.door_opening = 0;
	vars->player.door_closing = 0;
}

static void	init_doors_dir(t_object **map, int i, int j)
{
	if (map[i][j + 1].type == '1' && map[i][j - 1].type == '1'
			&& map[i + 1][j].type == '0' && map[i - 1][j].type == '0')
		map[i][j].orientation = NS;
	else
		map[i][j].orientation = WE;
	map[i][j].status = 1.0f;
}

void	init_objects(t_vars *vars, t_object **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j].type)
		{
			if (map[i][j].type && (map[i][j].type == 'N'
				|| map[i][j].type == 'S'
				|| map[i][j].type == 'W' || map[i][j].type == 'E'))
			{
				vars->player.x = j + 0.5f;
				vars->player.y = i + 0.5f;
				vars->player.orientation = map[i][j].type;
				map[i][j].type = '0';
			}
			if (map[i][j].type && map[i][j].type == 'D')
				init_doors_dir(map, i, j);
			j++;
		}
		i++;
	}
}
