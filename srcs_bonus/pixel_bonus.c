/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:32:00 by mdesrose          #+#    #+#             */
/*   Updated: 2023/11/20 15:20:56 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/cub3d_bonus.h"

// void	ft_draw_pixels_grid(void* param)
// {
// 	int x = 0;
// 	int y = 0;
// 	int	i = 0;

// 	t_vars *vars;

// 	vars = param;
// 	while (vars->map[y])
// 	{
// 		x = 0;
// 		while (vars->map[y][x])
// 		{
// 			i = 0;
// 			while (i < 10)
// 			{
// 				int j = 0;
// 				while (j < 10)
// 				{
// 					if (vars->map[y][x] == '1' || j == 0 || i == 0)
// 						mlx_put_pixel(vars->game, x * 10 + j, y * 10 + i, create_rgba(0, 0, 0, 150));
// 					else if (vars->map[y][x] == ' ')
// 						mlx_put_pixel(vars->game, x * 10 + j, y * 10 + i, create_rgba(0, 0, 0, 0));
// 					else
// 						mlx_put_pixel(vars->game, x * 10 + j, y * 10 + i, create_rgba(255, 255, 255, 150));
// 					j++;
// 				}
// 				i++;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// int	check_wall(t_vars *vars, double x, double y)
// {
// 	/*int	i;
// 	int	j;

// 	i = 0;
// 	while (vars->map[i])
// 	{
// 		j = 0;
// 		while (vars->map[i][j].type)
// 		{
// 			if (vars->map[i][j].type == '1' && (y > i * 50 && y < (i + 1) * 50)
// 			|| (x > j * 50 && x < (j + 1) * 50))
// 				return (0);
// 			j++;
// 		}
// 		i++;
// 	}*/
// 	if (vars->map[(int)(y / 50)][(int)(x / 50)] == '1')
// 		return (0);
// 	return (1);
// }

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

// void ft_draw_pixels_player(void* param, t_ray ray)
// {
// 	int x = 0;
// 	int y;
// 	t_vars *vars;

// 	vars = param;
// 	while (x < 3)
// 	{
// 		y = 0;
// 		while (y < 3)
// 		{
// 			mlx_put_pixel(vars->game, (int)(vars->player.x * 10 + x), (int)(vars->player.y * 10 + y), create_rgba(255, 0, 0, 150));
// 			y++;
// 		}
// 		x++;
// 	}
// }
