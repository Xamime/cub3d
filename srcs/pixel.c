/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:32:00 by mdesrose          #+#    #+#             */
/*   Updated: 2023/10/22 06:54:48 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	check_wall(t_vars *vars, double x, double y)
{
	/*int	i;
	int	j;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '1' && (y > i * 50 && y < (i + 1) * 50)
			|| (x > j * 50 && x < (j + 1) * 50))
				return (0);
			j++;
		}
		i++;
	}*/
	if (vars->map[(int)(y / 50)][(int)(x / 50)] == '1')
		return (0);
	return (1);
}

/*void    dda(t_vars *vars, t_point start, t_point end)
{
	double   	len_x;
	double      len_y;
	double 	 	step;
	double i = 0;
	double			x = start.x;
	double			y = start.y;
	double dx;
	double dy;
	int toto = 1;

	len_x = (end.x - start.x);
	len_y = (end.y - start.y);
	if (fabs(len_x) >= fabs(len_y))
		step = fabs(len_x);
	else
		step = fabs(len_y);
	dx = len_x / step;
	dy = len_y / step;
	while (i < HEIGHT)
	{
		if (x < HEIGHT && x > 0 && y < HEIGHT && y > 0 && check_wall(vars, x, y))
			mlx_put_pixel(vars->minimap, x, y, 0x232D8F);
		else
			break;
		x += dx;
		y += dy;
		i++;
	}
}*/

void ft_draw_pixels_player(void* param)
{
	int x = 0;
	int y;
	t_vars *vars;

	vars = param;
	//dda(vars, start, end);
	/*end.x = vars->player.x + 3 + (SPEED * vars->player.ray.deltadistX) - vars->player.ray.plane.x;
	end.y = vars->player.y + 3 + (SPEED * vars->player.ray.deltadistY) - vars->player.ray.plane.y;
	dda(vars, start, end);
	end.x = vars->player.x + 3 + (SPEED * vars->player.ray.deltadistX) + vars->player.ray.plane.x;
	end.y = vars->player.y + 3 + (SPEED * vars->player.ray.deltadistY) + vars->player.ray.plane.y;
	//printf("startx = %d, starty = %d endx = %d endy = %d dtx= %f dty = %f\n", start.x, start.y, end.x, end.y,vars->player.ray.deltadistX,vars->player.ray.deltadistY);
	dda(vars, start, end);*/
	while (x < 6)
	{
		y = 0;
		while (y < 6)
		{
			mlx_put_pixel(vars->player.image, x, y, 0xFF0000FF);
			y++;
		}
		x++;
	}
}
