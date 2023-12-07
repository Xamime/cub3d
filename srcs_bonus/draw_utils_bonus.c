/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:45:26 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/07 18:34:36 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	get_pixel_color(int i, int j, mlx_image_t *map_img)
{
	int	width;
	int	*pixel_color;
	int	rgb[3];

	width = map_img->width;
	pixel_color = (int *)map_img->pixels + (j * width + i);
	rgb[0] = (*pixel_color << 8) >> 24 & 0xFF;
	rgb[1] = (*pixel_color << 16) >> 24 & 0xFF;
	rgb[2] = (*pixel_color << 24) >> 24 & 0xFF;
	return (rgb[0] << 8 | rgb[1] << 16 | rgb[2] << 24 | 255);
}

void	set_ray_draw_pos(t_ray *ray)
{
	ray->lineheight = (int)(HEIGHT / ray->wall_dist);
	ray->drawstart = HEIGHT / 2 - ray->lineheight / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = HEIGHT / 2 + ray->lineheight / 2;
	if (ray->drawend >= HEIGHT)
		ray->drawend = HEIGHT - 1;
}
