/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:15:04 by jfarkas           #+#    #+#             */
/*   Updated: 2023/10/21 18:36:07 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	create_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_display_single_pixel(t_vars *vars, double x, double y, int color)
{
	if (WIDTH / 2 + x < WIDTH && HEIGHT / 2 + y < HEIGHT && WIDTH / 2 + x > 0 && HEIGHT / 2 + y > 0)
		mlx_put_pixel(vars->game, WIDTH / 2 + x, HEIGHT / 2 + y, color);
}

void	ft_display_distance(t_vars *vars, double x, double y, int color)
{
	// for (int i = HEIGHT - 1; i > HEIGHT - y; i--)
	// 	mlx_put_pixel(vars->game, x, i, color);
	if (HEIGHT - y > 0)
		mlx_put_pixel(vars->game, x, HEIGHT - y, color);
}

void	ft_display_single_ray(t_vars *vars, double x, double y, int color)
{
	double	tmp_x = 0.0f;
	double	tmp_y = 0.0f;

	if (!x || !y)
		return ;
	while (WIDTH / 2 + tmp_x < WIDTH && HEIGHT / 2 + tmp_y < HEIGHT && WIDTH / 2 + tmp_x > 0 && HEIGHT / 2 + tmp_y > 0)
	{
		mlx_put_pixel(vars->game, WIDTH / 2 + tmp_x, HEIGHT / 2 + tmp_y, color);
		tmp_x += x;
		tmp_y -= y;
	}
}

void	ft_update_offset_pos(int *step, double *side_dist, int step_val, double offset, double delta)
{
		*step = step_val;
		*side_dist = offset * delta;
}

void	ft_set_ray_dir(double *dir_x, double *dir_y, int x, t_ray *ray)
{
	int		fov = 90;

	double	start_dir_x;
	double	start_dir_y;
	double	start_angle = (fov / 2) * (PI / 180.0f);
	start_dir_x = ray->dirx * cos(start_angle) - ray->diry * sin(start_angle);
	start_dir_y = ray->dirx * sin(start_angle) + ray->diry * cos(start_angle);

	double	end_dir_x;
	double	end_dir_y;
	double	end_angle = -(fov / 2) * (PI / 180.0f);
	end_dir_x = ray->dirx * cos(end_angle) - ray->diry * sin(end_angle);
	end_dir_y = ray->dirx * sin(end_angle) + ray->diry * cos(end_angle);

	double	angle;
	double	rot_step = (double)-fov / WIDTH;
	angle = (double)(rot_step * x) * (PI / 180.0f);
	*dir_x = start_dir_x * cos(angle) - start_dir_y * sin(angle);
	*dir_y = start_dir_x * sin(angle) + start_dir_y * cos(angle);
}

void	ft_display_rays(t_vars *vars, t_ray *ray)
{
	double	camera_step;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	double	wall_dist;
	int		line_height;

	printf("\n");
	int		fov = 90;

	double	start_dir_x;
	double	start_dir_y;
	double	start_angle = (fov / 2) * (PI / 180.0f);
	start_dir_x = ray->dirx * cos(start_angle) - ray->diry * sin(start_angle);
	start_dir_y = ray->dirx * sin(start_angle) + ray->diry * cos(start_angle);

	double	end_dir_x;
	double	end_dir_y;
	double	end_angle = -(fov / 2) * (PI / 180.0f);
	end_dir_x = ray->dirx * cos(end_angle) - ray->diry * sin(end_angle);
	end_dir_y = ray->dirx * sin(end_angle) + ray->diry * cos(end_angle);

	double	angle;
	double	rot_step = (double)-fov / WIDTH;

	// double	dir_x = ray->dirx;
	// double	dir_y = ray->diry;
	// double	oldDirX = dir_x;
	// double	corr_angle = 44.7;
	// dir_x = dir_x * cos(corr_angle) - dir_y * sin(corr_angle);
	// dir_y = oldDirX * sin(corr_angle) + dir_y * cos(corr_angle);
	// double	plane_x;
	// double	plane_y;
	// angle = -90.0f * (PI / 180.0f);
	// plane_x = ray->dirx * cos(angle) - ray->diry * sin(angle);
	// plane_y = ray->dirx * sin(angle) + ray->diry * cos(angle);

	for (int x = 0; x < WIDTH; x += 5)
	{
		map_x = (int)(vars->player.x);
		map_y = (int)(vars->player.y);

		// ray->camerax = 2 * x / (double)(WIDTH - 1);
		// ray_dir_x = dir_x + ray->plane_x * ray->camerax;
		// ray_dir_y = dir_y + ray->plane_y * ray->camerax;

		ft_set_ray_dir(&ray_dir_x, &ray_dir_y, x, ray);
		ft_display_single_ray(vars, ray_dir_x, ray_dir_y, create_rgba(0, 255, 0, 255));

		delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		if (ray_dir_x < 0)
			ft_update_offset_pos(&step_x, &side_dist_x, -1, vars->player.x - map_x, delta_dist_x);
		else
			ft_update_offset_pos(&step_x, &side_dist_x, 1, map_x + 1.0 - vars->player.x, delta_dist_x);
		if (ray_dir_y < 0)
			ft_update_offset_pos(&step_y, &side_dist_y, -1, vars->player.y - map_y, delta_dist_y);
		else
			ft_update_offset_pos(&step_y, &side_dist_y, 1, map_y + 1.0 - vars->player.y, delta_dist_y);
		hit = 0;
		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			// ft_display_single_pixel(vars, side_dist_x * 10, -(side_dist_y * 10), create_rgba(255, 0, 255, 255));
			if (side)
				ft_display_distance(vars, x, side_dist_x * 40, create_rgba(0, 0, 255, 255));
			else
				ft_display_distance(vars, x, side_dist_y * 40, create_rgba(0, 0, 255, 255));
			if (map_y < 0.25	|| map_x < 0.25 || map_y > 7 - 0.25
				|| map_x > 7 - 1.25)
					break ;
			if (vars->map[map_y][map_x] == '1')
				hit = 1;
		}
		if (side == 0)
			wall_dist = (side_dist_x - delta_dist_x);
		else
			wall_dist = (side_dist_y - delta_dist_y);
		line_height = (int)(HEIGHT / wall_dist);
		if (line_height / 2 < HEIGHT / 2)
			ft_display_distance(vars, x, HEIGHT / 2 - line_height / 2, create_rgba(255, 255, 255, 255));
	}
	ft_display_single_ray(vars, start_dir_x, start_dir_y, create_rgba(255, 0, 0, 255));
	ft_display_single_ray(vars, end_dir_x, end_dir_y, create_rgba(0, 0, 255, 255));
	ft_display_single_ray(vars, ray->dirx, ray->diry, create_rgba(255, 255, 0, 255));
	// ft_display_single_ray(vars, plane_x, plane_y, create_rgba(255, 150, 255, 255));
	// ft_display_single_ray(vars, ray->plane_x, ray->plane_y, create_rgba(255, 0, 255, 255));
	printf("player.x : %f, player.y : %f\n", vars->player.x, vars->player.y);
	printf(RED"ray->dirx : %f, ray->diry : %f\n"DEFAULT_COL, ray->dirx, ray->diry);
	// printf(YELLOW"ray->plane_x : %f, ray->plane_y : %f\n"DEFAULT_COL, ray->plane_x, ray->plane_y);
	// printf(BLUE"plane_x : %f, plane_y : %f\n"DEFAULT_COL, plane_x, plane_y);
}
