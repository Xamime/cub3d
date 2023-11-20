/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:56:26 by max               #+#    #+#             */
/*   Updated: 2023/11/13 17:42:00 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define MINIMAP_WIDTH 200
#define MINIMAP_HEIGHT 200

uint32_t	put_color(t_vars *vars, double x, double y)
{
	if (vars->map[(int)y][(int)x].type == '1')
		return (create_rgba(255, 255, 255, 255));
	else if (vars->map[(int)y][(int)x].type == ' ')
		return (create_rgba(0, 0, 0, 0));
	// else if ((int)x + 1 - x < 0.01f || (int)x + 1 - x < 0.09f || (int)y + 1 - y < 0.01f || (int)y + 1 - y < 0.09f)
	// 	return (create_rgba(0, 0, 0, 255));
	return (create_rgba(0, 0, 0, 0));
}

void	draw_minimap(t_vars *vars)
{
	int	x = 0;
	int	y = 0;
	int	i = 0;
	int	j = 0;
	double	map_x;
	double	map_y;

	x = WIDTH - MINIMAP_WIDTH - 1;
	map_x = vars->player.x - (MINIMAP_WIDTH / vars->case_size) / 2;
	map_y = vars->player.y - (MINIMAP_HEIGHT / vars->case_size) / 2;
	double	step = 1.0f / vars->case_size;

	int	max_y = 0;

	while (vars->map[max_y])
		max_y++;

	// while (x < WIDTH)
	// {
	// 	y = HEIGHT - MINIMAP_HEIGHT - 1;
	// 	while (y < HEIGHT)
	// 	{
	// 		mlx_put_pixel(vars->game, x, y, create_rgba(0, 0, 0, 255));
	// 		y++;
	// 	}
	// 	x++;
	// }

	uint32_t	color;

	x = WIDTH - MINIMAP_WIDTH - 1;
	while (x < WIDTH)
	{
		y = HEIGHT - MINIMAP_HEIGHT - 1;
		map_y = vars->player.y - (MINIMAP_HEIGHT / vars->case_size) / 2;
		while (y < HEIGHT)
		{
			if (map_y > 0.0f && map_y < (double)max_y && map_x > 0.0f && map_x < ft_line_len(vars->map[(int)map_y]))
			{
				color = put_color(vars, map_x, map_y);
				if (color)
					mlx_put_pixel(vars->game, x, y, put_color(vars, map_x, map_y));
			}
			y++;
			map_y += step;
		}
		x++;
		map_x += step;
	}

	int	player_size;

	player_size = 5;
	x = WIDTH - MINIMAP_WIDTH / 2 - 1;
	while (x < WIDTH - MINIMAP_WIDTH / 2 - 1 + player_size)
	{
		y = HEIGHT - MINIMAP_HEIGHT / 2 - 1;
		while (y < HEIGHT - MINIMAP_HEIGHT / 2 - 1 + player_size)
		{
			mlx_put_pixel(vars->game, x, y, create_rgba(255, 0, 0, 150));
			y++;
		}
		x++;
	}
}
