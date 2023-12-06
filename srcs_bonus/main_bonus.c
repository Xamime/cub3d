/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/12/06 21:52:49 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	update_doors(t_object **map, t_player player)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x].type)
		{
			if (map[y][x].type == 'D')
			{
				map[y][x].mode = player.door_status;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	update_buffer(t_player *player, t_object **map, mlx_image_t *textures[4], uint32_t *buffer)
{
	t_dda			dda;
	t_ray			ray;
	t_render_tex	rtex;

	// printf("\n --- draw --- \n\n");

	update_doors(map, *player);
	for (int x = 0; x < WIDTH; x++)
	{
		ray.camerax = (2.0f / (double)(WIDTH - 1)) * x; // pas droit quand different de 2.0 ?
		ray.ray_dir.x = (player->dir.x + player->plane.x) - (player->plane.x * ray.camerax);
		ray.ray_dir.y = (player->dir.y + player->plane.y) - (player->plane.y * ray.camerax);
		dda = init_dda(*player, ray.ray_dir);
		ray.wall_dist = get_wall_dist(player, ray.ray_dir, &dda, map);
		set_ray_draw_pos(&ray);
		rtex = set_render_texture(*player, ray, &dda, textures);
		draw_wall(ray, rtex, x, buffer);
	}
}

void	draw_crosshair(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < 9)
	{
		x = 0;
		while (x < 9)
		{
			x++;
			if ((y >= 3 && y <= 5) || (x >= 3 && x <= 5))
				mlx_put_pixel(vars->crosshair, x, y, 0xFFFFFF);
		}
		y++;
	}
}

void	hook_again(t_vars *vars)
{
	vars->time += vars->mlx->delta_time;
	if (vars->time > 0.0125f)
	{
		// if (vars->player.is_door)
		// 	printf("is closing\n");
		// else
		// 	printf("is opening\n");
		if (vars->player.is_door == 1)
		{
			if (vars->player.door_status > 0.0f)
				vars->player.door_status -= 0.05f;
			else
				vars->player.is_door = 0;
		}
		else if (vars->player.is_door == 0)
		{
			if (vars->player.door_status < 1.0f)
				vars->player.door_status += 0.05f;
			else
				vars->player.is_door = 1;
		}
		vars->time = 0.0f;
	}
	// if (vars->time > 1.0f)
	// {
	// 	vars->time = 0.0f;
	// 	// printf("sec\n");
	// }
	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_ADD))
		vars->case_size *= 1.1f;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_SUBTRACT))
	{
		if (vars->case_size > 1.0f)
			vars->case_size *= 0.9f;
	}
	init_buffer(vars);
	update_buffer(&vars->player, vars->map, vars->textures, vars->buffer);
	draw_buffer(vars->game, vars->buffer);
	draw_minimap(vars);
	draw_crosshair(vars);
	vars->player.movespeed = vars->mlx->delta_time * 5.0;
	vars->player.rotspeed = vars->mlx->delta_time * 3.0;
}

void ft_hook(void* param)
{
	t_vars *vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		move(&vars->player, vars->map, LEFT);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		move(&vars->player, vars->map, RIGHT);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		move(&vars->player, vars->map, UP);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		move(&vars->player, vars->map, DOWN);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotate_left(&vars->player, vars->player.rotspeed);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotate_right(&vars->player, vars->player.rotspeed);
	hook_again(vars);

}

void cursor_change(double x, double y, void *param)
{
	t_vars			*vars;
	double			deltax;

	vars = (t_vars *)param;
	(void)y;
    deltax = x - WIDTH / 2;
    rotate_right(&vars->player, deltax / 400);
	mlx_set_mouse_pos(vars->mlx, WIDTH / 2, HEIGHT / 2);
}

int	main(int argc, const char* argv[])
{
	t_vars	vars;
	t_bg	bg;

	(void)argc;
	if (parse_file(&vars, argv[1], &bg))
		exit(1);

	find_pos(&vars, vars.map);
	init_orientation(&vars);

	vars.case_size = 10.0f;
	vars.player.door_status = 1.0f;
	vars.player.is_door = 1;
	vars.time = 0.0f;

	display_background(vars.mlx, bg);
	vars.game = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(vars.mlx, vars.game, 0, 0);
	update_buffer(&vars.player, vars.map, vars.textures, vars.buffer);
	vars.crosshair = mlx_new_image(vars.mlx, 9, 9);
	mlx_image_to_window(vars.mlx, vars.crosshair, WIDTH / 2 - 4, HEIGHT / 2 - 4);
	vars.minimap = mlx_new_image(vars.mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	mlx_image_to_window(vars.mlx, vars.minimap, WIDTH - MINIMAP_SIZE, HEIGHT - MINIMAP_SIZE);
	mlx_loop_hook(vars.mlx, ft_hook, &vars);
	mlx_set_cursor_mode(vars.mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(vars.mlx, WIDTH / 2, HEIGHT / 2);
	mlx_cursor_hook(vars.mlx, cursor_change, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	free_map(vars.map);
	free(vars.buffer);
	return (EXIT_SUCCESS);
}
