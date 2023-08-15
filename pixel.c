/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:32:00 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/15 19:51:20 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	ft_draw_pixels_grid(void* param)
{
	int x = 0;
	int y = 0;
	int	i = 0;
	
	t_vars *vars;

	vars = param;
	while (vars->map[y])
	{
		x = 0;
		while (vars->map[y][x])
		{
			i = 0;
			while (i < 50)
			{
				int j = 0;
				while (j < 50)
				{
					if (vars->map[y][x] == '1' || j == 0 || i == 0)
						mlx_put_pixel(vars->minimap, x * 50 + j, y * 50 + i, 0x000000FF);
					else
						mlx_put_pixel(vars->minimap, x * 50 + j, y * 50 + i, 0xFFFFFFFF);
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}
}

void    dda(t_vars *vars, t_point start, t_point end)
{
	double   	len_x;
	double      len_y;
	int  	 	step;
	int			x = start.x;
	int			y = start.y;
	
	len_x = (end.x - start.x);
	len_y = (end.y - start.y);
	if (fabs(len_x) >= fabs(len_y))
		step = fabs(len_x);
	else
		step = fabs(len_y);
	len_x = len_x / step;
	len_y = len_y / step;
	while (step--)
	{
		mlx_put_pixel(vars->minimap, x, y, 0xFF0000FF);
		x += len_x;
		y += len_y;
	}
}

void ft_draw_pixels_player(void* param)
{
	int x = 0;
	int y;
	t_vars *vars;

	vars = param;
	while (x < 10)
	{
		y = 0;
		while (y < 10)
		{
			mlx_put_pixel(vars->player.image, x, y, 0xFF0000FF);
			y++;
		}
		x++;
	}
	t_point	start;
	t_point end;

	start.x = vars->player.image->instances[0].x + 5;
	start.y = vars->player.image->instances[0].y;
	end.x = vars->player.image->instances[0].x + 5;
	end.y = vars->player.image->instances[0].y - 20;
	dda(vars, start, end);
}