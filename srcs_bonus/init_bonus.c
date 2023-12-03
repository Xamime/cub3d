/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:45:25 by max               #+#    #+#             */
/*   Updated: 2023/12/03 18:04:49 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void  init(t_vars *vars)
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
                vars->player.x = j;
                vars->player.y = i;
	            vars->player.orientation = map[i][j].type;
            }
            j++;
        }
        i++;
    }
}
