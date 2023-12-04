/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:34:19 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/04 03:47:20 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_wall(t_ray ray, t_render_tex rtex, int x, uint32_t *buffer)
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
