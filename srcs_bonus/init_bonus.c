/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:45:25 by max               #+#    #+#             */
/*   Updated: 2023/12/06 18:16:11 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_buffer(t_vars *vars)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			vars->buffer[y * WIDTH + x] = 0;
			x++;
		}
		y++;
	}
}

void	init_orientation(t_vars *vars)
{
	if (vars->player.orientation == 'N')
	{
		vars->player.dir.x = 0;
		vars->player.dir.y = -1;
		vars->player.plane.x = -0.5;
		vars->player.plane.y = 0;
	}
	else if (vars->player.orientation == 'E')
	{
		vars->player.dir.x = 1;
		vars->player.dir.y = 0;
		vars->player.plane.x = 0;
		vars->player.plane.y = -0.5;
	}
	else if (vars->player.orientation == 'W')
	{
		vars->player.dir.x = -1;
		vars->player.dir.y = 0;
		vars->player.plane.x = 0;
		vars->player.plane.y = 0.5;
	}
	else if (vars->player.orientation == 'S')
	{
		vars->player.dir.x = 0;
		vars->player.dir.y = 1;
		vars->player.plane.x = 0.5;
		vars->player.plane.y = 0;
	}
}

static void	init_doors_dir(t_object **map, int i, int j)
{
	if (map[i][j + 1].type == '1' && map[i][j - 1].type == '1'
			&& map[i + 1][j].type == '0' && map[i - 1][j].type == '0')
		map[i][j].orientation = WE;
	else if (map[i + 1][j].type == '1' && map[i - 1][j].type == '1'
			&& map[i][j + 1].type == '0' && map[i][j - 1].type == '0')
		map[i][j].orientation = NS;
}

void    find_pos(t_vars *vars, t_object **map)
{
    int i;
    int j;

    i = 0;
    while (map && map[i])
    {
        j = 0;
        while (map[i][j].type)
        {
            if (map[i][j].type && (map[i][j].type == 'N' || map[i][j].type == 'S'
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
