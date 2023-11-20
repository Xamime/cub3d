/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:15:04 by jfarkas           #+#    #+#             */
/*   Updated: 2023/11/20 15:20:56 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

uint32_t	create_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_display_single_pixel(t_vars *vars, double x, double y, int color)
{
	double	real_x = WIDTH / 2 + (x * vars->debug.zoom) + vars->debug.x_offset;
	double	real_y = HEIGHT / 2 + (y * vars->debug.zoom) + vars->debug.y_offset;

	if (real_x < WIDTH && real_y < HEIGHT && real_x > 0 && real_y > 0)
		mlx_put_pixel(vars->game, real_x, real_y, color);
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

void	ft_display_single_ray2(t_vars *vars, t_fpoint a, t_fpoint b, int color)
{
	a.x = a.x * vars->debug.zoom + vars->debug.x_offset;
	a.y = a.y * vars->debug.zoom + vars->debug.y_offset;
	b.x = b.x * vars->debug.zoom + vars->debug.x_offset;
	b.y = b.y * vars->debug.zoom + vars->debug.y_offset;
	double	tmp_x = WIDTH / 2 + a.x;
	double	tmp_y = HEIGHT / 2 + a.y;
	double	step_x = (b.x - a.x) / 100;
	double	step_y = (b.y - a.y) / 100;
	int		i = 0;

	if (!b.x || !b.y)
		return ;
	while (tmp_x < WIDTH && tmp_y < HEIGHT && tmp_x > 0 && tmp_y > 0 && i < 100)
	{
		mlx_put_pixel(vars->game, tmp_x, tmp_y, color);
		tmp_x += step_x;
		tmp_y -= step_y;
		i++;
	}
}

void	ft_update_offset_pos(int *step, double *side_dist, int step_val, double offset, double delta)
{
		*step = step_val;
		*side_dist = offset * delta;
}

static int	init_step(double ray_dir)
{
	if (ray_dir < 0)
		return (-1);
	else
		return (1);
}

static double	init_side_dist(double ray_dir, double player_pos, int map_pos, double delta)
{
	if (ray_dir < 0)
		return ((player_pos - map_pos) * delta);
	else
		return ((map_pos + 1.0f - player_pos) * delta);
}

static int	ccw(t_fpoint a, t_fpoint b, t_fpoint c)
{
	return ((c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x));
}

static int	intersect(t_fpoint a, t_fpoint b, t_fpoint c, t_fpoint d)
{
	return (ccw(a, c, d) != ccw(b, c, d) && ccw(a, b, c) != ccw(a, b, d));
}

void	perp_line(t_fpoint a, t_fpoint b, t_fpoint *c, t_fpoint *d)
{
	double	dx;
	double	dy;
	int		factor = 4;

	dx = a.x - b.x;
	dy = a.y - b.y;
	// c->x = a.x;
	// c->y = a.y;
	d->x = a.x + dy * factor;
	d->y = a.y - dx * factor;
}

static void	dda_loop(t_vars *vars, t_dda *dda, t_fpoint *side_dist, t_object **map, t_player player, t_fpoint ray_dir)
{
	double	test;
	double	test2;
	t_fpoint	vec1[2];
	t_fpoint	vec2[2];

	vec1[0].x = player.x + ray_dir.x;
	vec1[0].y = player.y + ray_dir.y;

	// if (ray_dir.x > -0.001f && ray_dir.x < 0.001f)
	// 	printf("is middle\n");

	printf("start sidedist_x : %f\n", side_dist->x);
	printf("start sidedist_y : %f\n", side_dist->y);
	printf("length x : %f\n", ray_dir.x / ray_dir.y);
	printf("length y : %f\n", ray_dir.y / ray_dir.x);

	while (map[dda->map.y][dda->map.x].type != '1')
	{
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += dda->delta_dist.x;
			dda->side = 0;
			printf("sidedist_x : %f\n", side_dist->x);
			if (map[dda->map.y][dda->map.x].type == 'D')
			{
				// vec1[0].x = side_dist->x - dda->delta_dist.x;
				// vec1[0].y = side_dist->y - dda->delta_dist.y;
				vec1[1].x = player.y - side_dist->y;
				vec1[1].y = side_dist->x + player.x;
				vec2[0].x = dda->map.x + dda->step.x / 2.0f;
				vec2[0].y = dda->map.y;
				vec2[1].x = dda->map.x + dda->step.x / 2.0f;
				vec2[1].y = dda->map.y + dda->step.y;
				// printf("map.x : %f, map.y : %f\n", vec2[0].x, vec2[0].y);
				// if (ray_dir.x > -0.001f && ray_dir.x < 0.001f)
				// {
				// 	printf("A.x : %f, A.y : %f, B.x : %f, B.y : %f\n", vec1[0].x, vec1[0].y, vec1[1].x, vec1[1].y);
				// 	printf("C.x : %f, C.y : %f, D.x : %f, D.y : %f\n", vec2[0].x, vec2[0].y, vec2[1].x, vec2[1].y);
				// }
				if (intersect(vec1[0], vec1[1], vec2[0], vec2[1]))
				{
					// printf("A.x : %f, A.y : %f, B.x : %f, B.y : %f\n", vec1[0].x, vec1[0].y, vec1[1].x, vec1[1].y);
					// printf("C.x : %f, C.y : %f, D.x : %f, D.y : %f\n", vec2[0].x, vec2[0].y, vec2[1].x, vec2[1].y);
					break ;
				}
			}
			// if (map[dda->map.y][dda->map.x].type == 'D')
			// 	break ;
			dda->map.x += dda->step.x;
		}
		else
		{
			side_dist->y += dda->delta_dist.y;
			dda->side = 1;
			printf("sidedist_y : %f\n", side_dist->y);
			if (map[dda->map.y][dda->map.x].type == 'D')
			{
				// if (ray_dir.y < 0.0f)
				// 	vec1[1].x = player.y - side_dist->y;
				// else
				// 	vec1[1].x = player.y + side_dist->y;
				// if (ray_dir.x < 0.0f)
				// 	vec1[1].y = player.x - side_dist->x;
				// else
				// 	vec1[1].y = player.x + side_dist->x;
				// wallX = player.x + ray.wall_dist * ray.ray_dir.x;
				perp_line(vec2[0], vec2[1], &vec1[0], &vec1[1]);
				vec2[0].x = dda->map.x;
				vec2[0].y = dda->map.y + dda->step.y / 2.0f;
				vec2[1].x = dda->map.x + dda->step.x;
				vec2[1].y = dda->map.y + dda->step.y / 2.0f;
				ft_display_single_ray2(vars, vec1[0], vec1[1], create_rgba(0, 0, 255, 255));
				ft_display_single_ray2(vars, vec2[0], vec2[1], create_rgba(255, 255, 255, 255));
				// printf("map.x : %f, map.y : %f\n", vec2[0].x, vec2[0].y);

				// if (ray_dir.x > -0.001f && ray_dir.x < 0.001f)
				// {
				// 	printf("A.x : %f, A.y : %f, B.x : %f, B.y : %f\n", vec1[0].x, vec1[0].y, vec1[1].x, vec1[1].y);
				// 	printf("C.x : %f, C.y : %f, D.x : %f, D.y : %f\n", vec2[0].x, vec2[0].y, vec2[1].x, vec2[1].y);
				// }
				if (intersect(vec1[0], vec1[1], vec2[0], vec2[1]))
				{
					// printf("A.x : %f, A.y : %f, B.x : %f, B.y : %f\n", vec1[0].x, vec1[0].y, vec1[1].x, vec1[1].y);
					// printf("C.x : %f, C.y : %f, D.x : %f, D.y : %f\n", vec2[0].x, vec2[0].y, vec2[1].x, vec2[1].y);
					break ;
				}
			}
			if (map[dda->map.y][dda->map.x].type == 'D')
				break ;
			dda->map.y += dda->step.y;
		}
		// if (map[dda->map.y][dda->map.x].type == 'D')
	}
}

double	get_wall_dist_debug(t_vars *vars, t_player player, t_fpoint ray_dir, t_dda *dda, t_object **map)
{
	t_fpoint	side_dist;

	side_dist.x = init_side_dist(ray_dir.x, player.x, dda->map.x, dda->delta_dist.x);
	side_dist.y = init_side_dist(ray_dir.y, player.y, dda->map.y, dda->delta_dist.y);
	// while (map[dda->map.y][dda->map.x].type != '1'/* && map[dda->map.y][dda->map.x].type != 'D'*/)
	// 	next_dda_step(dda, &side_dist);

	// printf("player.x : %f, player.y : %f\n", player.x, player.y);
	// printf("player.dir.x : %f, player.dir.y : %f\n", player.dir.x, player.dir.y);
	// side_dist.x += player.x;
	// side_dist.y += player.y;

	// printf("map_length : %d\n", player.map_length);
	// printf("ray_dir.x : %f\n", player.x + ray_dir.x);
	// printf("ray_dir.y : %f\n", player.y + ray_dir.y);

	ft_display_single_pixel(vars, (player.x + ray_dir.x), player.y + ray_dir.y, create_rgba(0, 255, 0, 255));
	ft_display_single_pixel(vars, player.x, player.y, create_rgba(0, 255, 0, 255));

	t_fpoint	a;
	t_fpoint	b;

	a.x = 24;
	a.y = 4.5f;
	b.x = 25;
	b.y = 4.5f;

	ft_display_single_ray2(vars, a, b, create_rgba(255, 255, 0, 255));

	dda_loop(vars, dda, &side_dist, map, player, ray_dir);

	if (dda->side == 0 && map[dda->map.y][dda->map.x].type == 'D')
	{
		// printf("coucou x\n");
		return (side_dist.x - dda->delta_dist.x - (dda->delta_dist.x / 2));
	}
	else if (dda->side == 1 && map[dda->map.y][dda->map.x].type == 'D')
	{
		// printf("coucou y\n");
		return (side_dist.y - dda->delta_dist.y - (dda->delta_dist.y / 2));
	}

	if (dda->side == 0)
		return (side_dist.x - dda->delta_dist.x);
	return (side_dist.y - dda->delta_dist.y);
}

void	ft_display_rays(t_vars *vars, t_player *player, t_object **map, mlx_image_t *textures[4], uint32_t *buffer)
{
	t_dda			dda;
	t_ray			ray;
	t_render_tex	rtex;

	// t_fpoint	a;
	// t_fpoint	b;
	// t_fpoint	c;
	// t_fpoint	d;

	// a.x = 22;
	// a.y = 8;
	// b.x = 27;
	// b.y = 8;

	// perp_line(a, b, &c, &d);

	// ft_display_single_ray2(vars, a, b, create_rgba(255, 0, 255, 255));
	// ft_display_single_ray2(vars, c, d, create_rgba(255, 0, 255, 255));

	static int	nb = 0;

	printf("\nframe %d\n", nb);

	for (int x = 0; x < WIDTH; x += 100)
	{
		printf("\n-----\n");
		ray.camerax = (2.0f / (double)(WIDTH - 1)) * x; // pas droit quand different de 2.0 ?
		ray.ray_dir.x = (player->dir.x + player->plane.x) - (player->plane.x * ray.camerax);
		ray.ray_dir.y = (player->dir.y + player->plane.y) - (player->plane.y * ray.camerax);
		dda = init_dda(*player, ray.ray_dir);
		ray.wall_dist = get_wall_dist_debug(vars, *player, ray.ray_dir, &dda, map);
		// set_ray_draw_pos(&ray);
		// rtex = set_render_texture(*player, ray, dda.side, textures);
		// draw_wall(ray, rtex, x, buffer);
	}

	nb++;
}


/*
void	ft_set_ray_dir(double *dir_x, double *dir_y, int x, t_ray *ray)
{
	int		fov = 90;

	double	start_dir_x;
	double	start_dir_y;
	double	start_angle = (fov / 2) * (PI / 180.0f);
	start_dir_x = player->dir.x * cos(start_angle) - player->dir.y * sin(start_angle);
	start_dir_y = player->dir.x * sin(start_angle) + player->dir.y * cos(start_angle);

	double	angle;
	double	rot_step = (double)-fov / WIDTH;
	angle = (double)(rot_step * x) * (PI / 180.0f);
	*dir_x = start_dir_x * cos(angle) - start_dir_y * sin(angle);
	*dir_y = start_dir_x * sin(angle) + start_dir_y * cos(angle);
}

void	ft_display_rays(t_vars *vars, t_ray *ray)
{
	//double	camera_step;
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

	for (int x = 0; x < WIDTH; x += 5)
	{
		map_x = (int)(vars->player.x);
		map_y = (int)(vars->player.y);

		camera_step = 2 * x / (double)(WIDTH - 1);
		ray_dir_x = player->dir.x + player->plane.x * camera_step;
		ray_dir_y = player->dir.y + player->plane.y * camera_step;

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
	// ft_display_single_ray(vars, start_dir_x, start_dir_y, create_rgba(255, 0, 0, 255));
	// ft_display_single_ray(vars, end_dir_x, end_dir_y, create_rgba(0, 0, 255, 255));
	ft_display_single_ray(vars, player->dir.x, player->dir.y, create_rgba(255, 255, 0, 255));
	// ft_display_single_ray(vars, plane.x, plane.y, create_rgba(255, 150, 255, 255));
	// ft_display_single_ray(vars, player->plane.x, player->plane.y, create_rgba(255, 0, 255, 255));
	printf("player.x : %f, player.y : %f\n", vars->player.x, vars->player.y);
	printf(RED"player->dir.x : %f, player->dir.y : %f\n"DEFAULT_COL, player->dir.x, player->dir.y);
	// printf(YELLOW"player->plane.x : %f, player->plane.y : %f\n"DEFAULT_COL, player->plane.x, player->plane.y);
	// printf(BLUE"plane.x : %f, plane.y : %f\n"DEFAULT_COL, plane.x, plane.y);
}
*/
