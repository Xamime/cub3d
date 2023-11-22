/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/11/21 22:30:40 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	display_fps(t_vars *vars)
{
	char	*str = NULL;
	char	*tmp;
	char	fps[15];

	ft_bzero(fps, 15);
	ft_itoa_no_malloc((int)(1.0 / vars->mlx->delta_time), fps);
	ft_strlcat(fps, " FPS", 16);
	mlx_set_window_title(vars->mlx, fps);
}

t_ray	 update_buffer(t_player *player, t_object **map, mlx_image_t *textures[4], uint32_t *buffer)
{
	t_dda			dda;
	t_ray			ray;
	t_render_tex	rtex;

	// printf("\n --- draw --- \n\n");

	for (int x = 0; x < WIDTH; x++)
	{
		ray.camerax = (2.0f / (double)(WIDTH - 1)) * x; // pas droit quand different de 2.0 ?
		ray.ray_dir.x = (player->dir.x + player->plane.x) - (player->plane.x * ray.camerax);
		ray.ray_dir.y = (player->dir.y + player->plane.y) - (player->plane.y * ray.camerax);
		dda = init_dda(*player, ray.ray_dir);
		ray.wall_dist = get_wall_dist(*player, ray.ray_dir, &dda, map);
		set_ray_draw_pos(&ray);
		rtex = set_render_texture(*player, ray, dda.side, textures);
		draw_wall(ray, rtex, x, buffer);
	}
	return (ray);
}

void	hook_debug(t_vars *vars)
{
	int	speed = 5;

	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_8))
	{
		vars->debug.y_offset -= speed;
		vars->player.has_moved = 1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_2))
	{
		vars->debug.y_offset += speed;
		vars->player.has_moved = 1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_6))
	{
		vars->debug.x_offset += speed;
		if (vars->player.door_status < 0.5f)
			vars->player.door_status += 0.0125f;
		vars->player.has_moved = 1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_4))
	{
		vars->debug.x_offset -= speed;
		if (vars->player.door_status > 0.0f)
			vars->player.door_status -= 0.0125f;
		vars->player.has_moved = 1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_ADD))
	{
		vars->debug.zoom += 1;
		vars->player.has_moved = 1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_SUBTRACT))
	{
		if (vars->debug.zoom > 1)
			vars->debug.zoom -= 1;
		vars->player.has_moved = 1;
	}
}

void	hook_again(t_vars *vars, t_ray ray)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_ADD))
	{
		vars->case_size *= 1.1f;
		vars->player.has_moved = 1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_SUBTRACT))
	{
		if (vars->case_size > 1.0f)
			vars->case_size *= 0.9f;
		vars->player.has_moved = 1;
	}
	hook_debug(vars);
	if (vars->player.has_moved)
	{
		init(vars);
		ray = update_buffer(&vars->player, vars->map, vars->textures, vars->buffer);
		draw_buffer(vars, vars->game, vars->buffer);
		draw_minimap(vars);
		vars->player.movespeed = vars->mlx->delta_time * 5.0;
		vars->player.rotspeed = vars->mlx->delta_time * 3.0;
		vars->player.has_moved = 0;
		// ft_display_rays(vars, &vars->player, vars->map, vars->textures, vars->buffer);
	}
	vars->time += vars->mlx->delta_time;
	if (vars->time > 1.0f)
	{
		vars->time = 0.0f;
		// printf("sec\n");
	}
}

void ft_hook(void* param)
{
	t_ray	ray;
	t_vars *vars;

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		left_step(&vars->player, vars->map);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		right_step(&vars->player, vars->map);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		ft_up(&vars->player, vars->map);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		ft_down(&vars->player, vars->map);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotate_left(&vars->player, vars->player.rotspeed);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotate_right(&vars->player, vars->player.rotspeed);
	hook_again(vars, ray);

}

void	cursor_hook(double x, double y, void *param)
{
	t_vars			*vars;
	static double	last_x = 0;

	vars = (t_vars *)param;
	rotate_right(&vars->player, (x - last_x) / 200);
	last_x = x;
	mlx_set_mouse_pos(vars->mlx, WIDTH / 2, HEIGHT / 2);
}

int	start_loop(t_vars *vars, const char *path)
{
	t_bgrd bgrd;

	vars->mlx = mlx_init(WIDTH, HEIGHT, "cub", true);
	alloc_buffer(vars);
	if (parse_file(vars, path, &bgrd))
		return (1);
	find_pos(vars, vars->map);
	init_orientation(vars);
	vars->case_size = 10.0f;
	vars->debug.x_offset = 0.0f;
	vars->debug.y_offset = 0.0f;
	vars->debug.zoom = 1;
	vars->player.door_status = 0.0f;
	display_background(vars->mlx, bgrd);
	vars->game = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->instance = mlx_image_to_window(vars->mlx, vars->game, 0, 0);
	update_buffer(&vars->player, vars->map, vars->textures, vars->buffer);
	// mlx_cursor_hook(vars->mlx, cursor_hook, vars);
	mlx_loop_hook(vars->mlx, ft_hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}

int	main(int32_t argc, const char* argv[])
{
	t_vars	vars;

	(void)argc;
	start_loop(&vars, argv[1]);
	// free_2d_array(vars.map);
	free_map(vars.map);
	free(vars.buffer);
	return (EXIT_SUCCESS);
}
