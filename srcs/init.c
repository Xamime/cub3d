/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:45:25 by max               #+#    #+#             */
/*   Updated: 2023/10/22 06:54:16 by jfarkas          ###   ########.fr       */
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
	vars->ray.lineheight = 0;
	vars->ray.drawend = 0;
	vars->ray.drawstart = 0;
	//vars->ray.camerax = 0;
	vars->dda.side = 0;

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
		vars->ray.dir.x = 0;
		vars->ray.dir.y = -1;
		vars->ray.plane.x = -0.66;
		vars->ray.plane.y = 0;
	}
	else if (vars->player.orientation == 'E')
	{
		vars->ray.dir.x = 1;
		vars->ray.dir.y = 0;
		vars->ray.plane.x = 0;
		vars->ray.plane.y = -0.66;
	}
	else if (vars->player.orientation == 'W')
	{
		vars->ray.dir.x = -1;
		vars->ray.dir.y = 0;
		vars->ray.plane.x = 0;
		vars->ray.plane.y = 0.66;
	}
	else if (vars->player.orientation == 'S')
	{
		vars->ray.dir.x = 0;
		vars->ray.dir.y = 1;
		vars->ray.plane.x = 0.66;
		vars->ray.plane.y = 0;
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
            if (map[i][j] != '0' && map[i][j] != '1')
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
