/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:34:19 by jfarkas           #+#    #+#             */
/*   Updated: 2023/10/22 09:49:03 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_ceiling(uint32_t *buffer, int x, int y)
{
	int	y1;

	y1 = 0;
	while (y1 < y)
	{
		buffer[y1 * WIDTH + x] = create_rgba(150, 150, 70, 255);
		y1++;
	}
}

void	draw_floor(uint32_t *buffer, int x, int y)
{
	while (y < HEIGHT)
	{
		buffer[y * WIDTH + x] = create_rgba(50, 50, 140, 255);
		y++;
	}
}

void	draw_wall(t_ray ray, t_render_tex rtex, int x, uint32_t *buffer)
{
	double		step = 1.0 * rtex.texture->height / ray.lineheight;
	double		start_pos = (ray.drawstart - HEIGHT / 2 + ray.lineheight / 2) * step;
	uint32_t	color;

	// tex_pos, tex_start_pos, tex, buffer, x
	for (int y = ray.drawstart; y < ray.drawend; y++)
	{
		// Cast the texture coordinate to integer, and mask with (tex->height - 1) in case of overflow
		rtex.pos.y = (int)start_pos & (rtex.texture->height - 1);
		start_pos += step;
		color = get_pixel_color(rtex.pos.x, rtex.pos.y, rtex.texture);
		buffer[y * WIDTH + x] = color;
	}
}

void	draw_buffer(t_vars *vars, mlx_image_t *game, uint32_t *buffer)
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			mlx_put_pixel(vars->game, x, y, buffer[y * WIDTH + x]);
		}
	}
}
