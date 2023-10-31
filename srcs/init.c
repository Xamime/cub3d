/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:45:25 by max               #+#    #+#             */
/*   Updated: 2023/10/31 15:05:57 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
}

void  init(t_vars *vars)
{
	for (int y = 0; y < HEIGHT; y++){
		for (int x = 0; x < WIDTH; x++){
			vars->buffer[y * WIDTH + x] = 0;
		}
	}
}

void	init_orientation(t_vars *vars)
{
	if (vars->player.orientation == 'N')
	{
		vars->player.dir.x = 0;
		vars->player.dir.y = -1;
		vars->player.plane.x = -0.66;
		vars->player.plane.y = 0;
	}
	else if (vars->player.orientation == 'E')
	{
		vars->player.dir.x = 1;
		vars->player.dir.y = 0;
		vars->player.plane.x = 0;
		vars->player.plane.y = -0.66;
	}
	else if (vars->player.orientation == 'W')
	{
		vars->player.dir.x = -1;
		vars->player.dir.y = 0;
		vars->player.plane.x = 0;
		vars->player.plane.y = 0.66;
	}
	else if (vars->player.orientation == 'S')
	{
		vars->player.dir.x = 0;
		vars->player.dir.y = 1;
		vars->player.plane.x = 0.66;
		vars->player.plane.y = 0;
	}
}

void    find_pos(t_vars *vars, char **map)
{
    int i;
    int j;

    i = 0;
    while (map && map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] && map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ')
            {
                vars->player.x = j;
                vars->player.y = i;
	            vars->player.orientation = map[i][j];
            }
            j++;
        }
        i++;
    }
}
