/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:56:26 by max               #+#    #+#             */
/*   Updated: 2023/12/07 13:31:11 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static uint32_t	get_color(t_object **map, double x, double y)
{
	t_object	obj;

	obj = map[(int)y][(int)x];
	if (obj.type == '1')
		return (create_rgba(255, 255, 255, 255));
	else if (obj.type == 'D' && obj.mode > 0.001f)
		return (create_rgba(255, 0, 0, 255));
	else if (obj.type == 'D' && obj.mode < 0.001f)
		return (create_rgba(0, 255, 0, 255));
	return (create_rgba(0, 0, 0, 0));
}

static void	draw_background(mlx_image_t *minimap)
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

static void	draw_player(mlx_image_t *minimap)
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

static void	put_pix_minimap(t_vars *vars, double map_x, double map_y, double step)
{
	int			x;
	int			y;
	uint32_t	color;

	x = 0;
	while (x < MINIMAP_SIZE)
	{
		y = 0;
		map_y = vars->player.y - (MINIMAP_SIZE / vars->case_size) / 2;
		while (y < MINIMAP_SIZE)
		{
			if (map_y > 0.0f && map_y < (double)get_mapsize(vars)
				&& map_x > 0.0f && map_x < ft_line_len(vars->map[(int)map_y]))
			{
				color = get_color(vars->map, map_x, map_y);
				if (color)
					mlx_put_pixel(vars->minimap, x, y, color);
			}
			y++;
			map_y += step;
		}
		x++;
		map_x += step;
	}
}

void	draw_minimap(t_vars *vars)
{
	double	map_x;
	double	map_y;
	double	step;

	map_x = vars->player.x - (MINIMAP_SIZE / vars->case_size) / 2;
	map_y = vars->player.y - (MINIMAP_SIZE / vars->case_size) / 2;
	step = 1.0f / vars->case_size;
	draw_background(vars->minimap);
	put_pix_minimap(vars, map_x, map_y, step);
	draw_player(vars->minimap);
}
