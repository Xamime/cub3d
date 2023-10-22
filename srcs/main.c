/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/10/22 06:54:52 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_ceiling(t_vars *vars, int x, int y)
{
	int	y1;

	y1 = 0;
	while (y1 < y)
	{
		vars->buffer[y1 * WIDTH + x] = create_rgba(150, 150, 70, 255);
		y1++;
	}
}

static void	draw_floor(t_vars *vars, int x, int y)
{
	while (y < HEIGHT)
	{
		vars->buffer[y * WIDTH + x] = create_rgba(50, 50, 140, 255);
		y++;
	}
}

mlx_image_t	*find_tex_side(t_vars *vars, int wallx, int side)
{
	(void)wallx;
	if (side == 0)
		return (vars->textures[EAST]);
	if (side)
		return (vars->textures[WEST]);
	return (vars->textures[NORTH]);
}

void drawBuffer(t_vars *vars, mlx_image_t *game, uint32_t *buffer)
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			mlx_put_pixel(vars->game, x, y, buffer[y * WIDTH + x]) ;
		}
	}
}

int    retrieve_pixel_color(int i, int j, mlx_image_t *map_img)
{
	int    width;
	int    *pixel_color;
	int    rgb[3];

	width = map_img->width;
	pixel_color = (int *)map_img->pixels + (j * width + i);
	rgb[0] = (*pixel_color << 8) >> 24 & 0xFF;
	rgb[1] = (*pixel_color << 16) >> 24 & 0xFF;
	rgb[2] = (*pixel_color << 24) >> 24 & 0xFF;
	return (rgb[0] << 8 | rgb[1] << 16 | rgb[2] << 24 | 255);
}

int	init_step(double ray_dir)
{
	if (ray_dir < 0)
		return (-1);
	else
		return (1);
}

double	init_side_dist(double ray_dir, double player_pos, int map_pos, double delta)
{
	if (ray_dir < 0)
		return ((player_pos - map_pos) * delta);
	else
		return ((map_pos + 1.0f - player_pos) * delta);
}

double	calculate_wall_dist(t_vars *vars, t_fpoint ray_dir, t_dda *dda)
{
	t_fpoint	side_dist;

	side_dist.x = init_side_dist(ray_dir.x, vars->player.x, dda->map.x, dda->delta_dist.x);
	side_dist.y = init_side_dist(ray_dir.y, vars->player.y, dda->map.y, dda->delta_dist.y);
	while (vars->map[dda->map.y][dda->map.x] != '1')
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += dda->delta_dist.x;
			dda->map.x += dda->step.x;
			dda->side = 0;
		}
		else
		{
			side_dist.y += dda->delta_dist.y;
			dda->map.y += dda->step.y;
			dda->side = 1;
		}
	}
	if (dda->side == 0)
		return (side_dist.x - dda->delta_dist.x);
	return (side_dist.y - dda->delta_dist.y);
}

t_dda	init_dda(t_player player, t_fpoint ray_dir)
{
	t_dda	dda;

	dda.map.x = (int)(player.x);
	dda.map.y = (int)(player.y);
	dda.delta_dist.x = (ray_dir.x == 0) ? 1e30 : fabs(1 / ray_dir.x);
	dda.delta_dist.y = (ray_dir.y == 0) ? 1e30 : fabs(1 / ray_dir.y);
	dda.step.x = init_step(ray_dir.x);
	dda.step.y = init_step(ray_dir.y);
	return (dda);
}

void	set_ray_draw_pos(t_ray *ray)
{
	ray->lineheight = (int)(HEIGHT / ray->wall_dist);
	ray->drawstart = HEIGHT / 2 - ray->lineheight / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = HEIGHT / 2 + ray->lineheight / 2;
	if (ray->drawend >= HEIGHT)
		ray->drawend = HEIGHT - 1;
}

void	 ft_draw_walls(t_vars *vars, t_ray *ray)
{
	double		camera_step = 2.0f / (double)(WIDTH - 1);
	double		start_x = ray->dir.x - ray->plane.x;
	double		start_y = ray->dir.y - ray->plane.y;
	uint32_t	color;

	t_dda		dda;

	init(vars);

	for (int x = 0; x < WIDTH; x++)
	{
		ray->camerax = camera_step * x;
		ray->ray_dir.x = start_x + (ray->plane.x * ray->camerax);
		ray->ray_dir.y = start_y + (ray->plane.y * ray->camerax);
		dda = init_dda(vars->player, ray->ray_dir);
		ray->wall_dist = calculate_wall_dist(vars, ray->ray_dir, &dda);
		set_ray_draw_pos(ray);
		//texturing calculations
		//int texNum = vars->map[dda->map.y][dda->map.x] - 1 - 48; //1 subtracted from it so that texture 0 can be used!
	  	//calculate value of wallX
	 	double wallX; //where exactly the wall was hit
	 	if (dda.side == 0)
			wallX = vars->player.y + ray->wall_dist * ray->ray_dir.y;
	 	else
			wallX = vars->player.x + ray->wall_dist * ray->ray_dir.x;
	 	wallX -= floor((wallX));
		//printf("wallx = %f\n",wallX);
	 	//x coordinate on the texture
	 	int texX = (int)(wallX * (double)texWidth);
	 	if(dda.side == 0 && ray->ray_dir.x > 0)
			texX = texWidth - texX - 1;
	 	if(dda.side == 1 && ray->ray_dir.y < 0)
			texX = texWidth - texX - 1;
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / ray->lineheight;
		// Starting texture coordinate
		double texPos = (ray->drawstart - HEIGHT / 2 + ray->lineheight / 2) * step;

		draw_ceiling(vars,x,vars->ray.drawstart);
		draw_floor(vars, x, ray->drawend);

		for(int y = ray->drawstart; y < ray->drawend; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			color = retrieve_pixel_color(texX,texY,find_tex_side(vars, wallX, dda.side));
			vars->buffer[y * WIDTH + x] = color;
		}
	}
	drawBuffer(vars, vars->game, vars->buffer);
	vars->player.movespeed = vars->mlx->delta_time * 5.0;
	vars->player.rotspeed = vars->mlx->delta_time * 3.0;
	// printf("fps = %f\n", 1.0 / vars->mlx->delta_time);
	// ft_display_rays(vars, ray);
}

void ft_hook(void* param)
{
	t_vars *vars  = param;

	//ft_draw_pixels_grid(vars);
	//ft_draw_pixels_player(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		left_step(vars, &vars->ray);
		ft_draw_walls(vars, &vars->ray);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		right_step(vars, &vars->ray);
		ft_draw_walls(vars, &vars->ray);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		ft_up(vars, &vars->ray);
		ft_draw_walls(vars, &vars->ray);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		ft_down(vars, &vars->ray);
		ft_draw_walls(vars, &vars->ray);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		rotate_left(vars, &vars->ray);
		ft_draw_walls(vars, &vars->ray);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		rotate_right(vars, &vars->ray);
		ft_draw_walls(vars, &vars->ray);
	}
	//vars->player.image->instances[0].x = (int)(vars->player.x * 50);
	//vars->player.image->instances[0].y = (int)(vars->player.y * 50);
	/*vars->minimap->instances[0].x = (int)(vars->player.x * 50);
	vars->minimap->instances[0].y = (int)(vars->player.y * 50);*/
}

int	start_loop(t_vars *vars)
{
	vars->mlx = mlx_init(WIDTH, HEIGHT, "cub", true);
	init_textures(vars);
	//reset_window(vars);
	vars->game = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->instance = mlx_image_to_window(vars->mlx, vars->game, 0, 0);
	ft_draw_walls(vars, &vars->ray);
	mlx_loop_hook(vars->mlx, ft_hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}


int	main(int32_t argc, const char* argv[])
{
	t_vars	vars;

	(void)argc;(void)argv;
	//system("clear");
	vars.map = ft_split("11111111:10000001:10000001:1010S001:10000001:10000001:10000001:11111111",':');
	find_pos(&vars, vars.map);
	init_orientation(&vars);
	start_loop(&vars);
	for (int i = 0; vars.map[i]; i++)
		free(vars.map[i]);
	free(vars.map);
	free(vars.buffer);
	return (EXIT_SUCCESS);
}
