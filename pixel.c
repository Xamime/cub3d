/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:32:00 by mdesrose          #+#    #+#             */
/*   Updated: 2023/09/13 19:41:01 by jfarkas          ###   ########.fr       */
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
	double 	 	step;
	double i = 0;
	int			x = start.x;
	int			y = start.y;
	
	len_x = (end.x - start.x);
	len_y = (end.y - start.y);
	if (fabs(len_x) >= fabs(len_y))
		step = fabs(len_x);
	else
		step = fabs(len_y);
	// printf("step%f lenx: %f\n",step, len_x);
	while (i < step)
	{
		if (x < 1024 && x > 0 && y < 1024 && y > 0 )
			mlx_put_pixel(vars->minimap, x, y, 0xFF0000FF);
		x += len_x;
		y += len_y;
		i += 1.0f;
	}
}

void	ft_draw_rays(t_vars *vars)
{
	int fov,r,mx,my,mp,dof; double rx,ry,xo,px,yo,py;
	py = vars->player.image->instances[0].y;
	px = vars->player.image->instances[0].x;
	vars->player.ray.angle = vars->player.angle;
	
	for (r = 0; r < 1;r++)
	{
		dof = 0;
		double aTan = -1/tan(vars->player.ray.angle);
		if (vars->player.ray.angle > PI)
		{
			ry =(((int)py>>6)<<6)-0.0001;
			rx = (py - ry) * aTan + px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (vars->player.ray.angle < PI)
		{
			ry =(((int)py>>6)<<6) + 64;
			rx = (py - ry) * aTan + px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (vars->player.ray.angle == 0 || vars->player.ray.angle == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int) (rx)>>6;
			my = (int) (ry)>>6;
			mp = my * 8 + mx;
			//if (mp < 8 * 8 && vars->map[])
		}
	}
}

void ft_draw_pixels_player(void* param)
{
	int x = 0;
	int y;
	t_vars *vars;
	t_point	start;
	t_point end;

	vars = param;
	//ft_draw_rays(vars);
	start.x = vars->player.image->instances[0].x + 5;
	start.y = vars->player.image->instances[0].y + 5;
	end.x = vars->player.image->instances[0].x + 5 * vars->player.ray.deltadistX;
	end.y = vars->player.image->instances[0].y + 5 * vars->player.ray.deltadistY;

	double   	len_x;
	double      len_y;
	double 	 	step;
	
	len_x = (end.x - start.x);
	len_y = (end.y - start.y);
	if (fabs(len_x) >= fabs(len_y))
		step = fabs(len_x);
	else
		step = fabs(len_y);
	printf("step : %f / len_x : %f / len_y : %f\n",step, len_x, len_y);
	dda(vars, start, end);
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
}