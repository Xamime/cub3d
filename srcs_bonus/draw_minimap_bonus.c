/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:56:26 by max               #+#    #+#             */
/*   Updated: 2023/12/06 22:01:25 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

uint32_t	get_color(t_object **map, double x, double y)
{
	if (map[(int)y][(int)x].type == '1')
		return (create_rgba(255, 255, 255, 255));
	else if (map[(int)y][(int)x].type == ' ')
		return (create_rgba(0, 0, 0, 0));
	return (create_rgba(0, 0, 0, 0));
}

void	draw_background(mlx_image_t *minimap)
{
	int	x;
	int	y;

	x = 0;
	while (x < MINIMAP_SIZE)
	{
		y = 0;
		while (y < MINIMAP_SIZE)
		{
			mlx_put_pixel(minimap, x, y, create_rgba(0, 0, 0, 100));
			y++;
		}
		x++;
	}
}

void	draw_player(mlx_image_t *minimap)
{
	int	x;
	int	y;

	x = MINIMAP_SIZE / 2 - 1;
	while (x < MINIMAP_SIZE / 2 - 1 + MINIMAP_PLAYER_SIZE)
	{
		y = MINIMAP_SIZE / 2 - 1;
		while (y < MINIMAP_SIZE / 2 - 1 + MINIMAP_PLAYER_SIZE)
		{
			mlx_put_pixel(minimap, x, y, create_rgba(255, 0, 0, 255));
			y++;
		}
		x++;
	}
}

void	draw_minimap(t_minimap *minimap, t_player player, t_object **map)
{
	int	x = 0;
	int	y = 0;
	double	map_x;
	double	map_y;

	x = 0;
	map_x = player.x - (MINIMAP_SIZE / minimap->case_size) / 2;
	map_y = player.y - (MINIMAP_SIZE / minimap->case_size) / 2;
	double	step = 1.0f / minimap->case_size;

	int	max_y = 0;

	while (map[max_y])
		max_y++;

	draw_background(minimap->image);

	uint32_t	color;

	x = 0;
	while (x < MINIMAP_SIZE)
	{
		y = 0;
		map_y = player.y - (MINIMAP_SIZE / minimap->case_size) / 2;
		while (y < MINIMAP_SIZE)
		{
			if (map_y > 0.0f && map_y < (double)max_y && map_x > 0.0f && map_x < ft_line_len(map[(int)map_y]))
			{
				color = get_color(map, map_x, map_y);
				if (color)
					mlx_put_pixel(minimap->image, x, y, get_color(map, map_x, map_y));
			}
			y++;
			map_y += step;
		}
		x++;
		map_x += step;
	}
	draw_player(minimap->image);
}
