/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:45:25 by max               #+#    #+#             */
/*   Updated: 2023/10/16 20:17:39 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

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
	vars->ray.hit = 0;
	vars->ray.side = 0;
}

void	init_textures(t_texture *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor = 0;
	textures->ceiling = 0;
	textures->hex_floor = 0x0;
	textures->hex_ceiling = 0x0;
	textures->size = 50;
	textures->step = 0.0;
	textures->pos = 0.0;
	textures->x = 0;
	textures->y = 0;
}

void	init_orientation(t_vars *vars)
{
	if (vars->player.orientation == 'N')
	{
		vars->ray.dirx = 0;
		vars->ray.diry = -1;
	}
	else if (vars->player.orientation == 'E')
	{
		vars->ray.dirx = 1;
		vars->ray.diry = 0;
	}
	else if (vars->player.orientation == 'W')
	{
		vars->ray.dirx = -1;
		vars->ray.diry = 0;
	}
	else if (vars->player.orientation == 'S')
	{
		vars->ray.dirx = 0;
		vars->ray.diry = 1;
	}
}
