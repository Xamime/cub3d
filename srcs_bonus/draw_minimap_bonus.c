/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:56:26 by max               #+#    #+#             */
/*   Updated: 2023/12/06 14:53:57 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

uint32_t	put_color(t_vars *vars, double x, double y)
{
	if (vars->map[(int)y][(int)x].type == '1')
		return (create_rgba(255, 255, 255, 255));
	else if (vars->map[(int)y][(int)x].type == ' ')
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
			mlx_put_pixel(minimap, x, y, create_rgba(255, 0, 0, 150));
			y++;
		}
		x++;
	}
}

void	draw_minimap(t_vars *vars)
{
	int	x = 0;
	int	y = 0;
	double	map_x;
	double	map_y;

	x = 0;
	map_x = vars->player.x - (MINIMAP_SIZE / vars->case_size) / 2;
	map_y = vars->player.y - (MINIMAP_SIZE / vars->case_size) / 2;
	double	step = 1.0f / vars->case_size;

	int	max_y = 0;

	while (vars->map[max_y])
		max_y++;

	draw_background(vars->minimap);

	uint32_t	color;

	x = 0;
	while (x < MINIMAP_SIZE)
	{
		y = 0;
		map_y = vars->player.y - (MINIMAP_SIZE / vars->case_size) / 2;
		while (y < MINIMAP_SIZE)
		{
			if (map_y > 0.0f && map_y < (double)max_y && map_x > 0.0f && map_x < ft_line_len(vars->map[(int)map_y]))
			{
				color = put_color(vars, map_x, map_y);
				if (color)
					mlx_put_pixel(vars->minimap, x, y, put_color(vars, map_x, map_y));
			}
			y++;
			map_y += step;
		}
		x++;
		map_x += step;
	}
	draw_player(vars->minimap);
}
