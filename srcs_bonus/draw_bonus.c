/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:34:19 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/07 19:51:56 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_crosshair(mlx_image_t *crosshair)
{
	int	x;
	int	y;

	y = 0;
	while (y < 18)
	{
		x = 0;
		while (x < 18)
		{
			if ((y >= (18 - 1) / 2 && y <= (18 - 1) / 2 + 1)
				|| (x >= (18 - 1) / 2 && x <= (18 - 1) / 2 + 1))
				mlx_put_pixel(crosshair, x, y,
					create_rgba(255, 255, 255, 255));
			x++;
		}
		y++;
	}
}

void	draw_wall(t_ray ray, t_rtex rtex, int x, uint32_t *buffer)
{
	double		step;
	double		tex_y;
	uint32_t	color;
	int			y;

	y = ray.drawstart;
	step = 1.0 * rtex.texture->height / ray.lineheight;
	tex_y = (ray.drawstart - HEIGHT / 2 + ray.lineheight / 2) * step;
	while (y < ray.drawend)
	{
		color = get_pixel_color(rtex.pos.x, (int)tex_y, rtex.texture);
		buffer[y * WIDTH + x] = color;
		tex_y += step;
		y++;
	}
}

void	draw_buffer(mlx_image_t *game, uint32_t *buffer)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game, x, y, buffer[y * WIDTH + x]);
			x++;
		}
		y++;
	}
}
