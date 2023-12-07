/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/12/07 15:51:13 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_buffer(t_player *player, char **map,
	mlx_image_t *textures[4], uint32_t *buffer)
{
	t_dda			dda;
	t_ray			ray;
	t_render_tex	rtex;
	int				x;

	x = 0;
	while (x < WIDTH)
	{
		ray.camerax = (2.0f / (double)(WIDTH - 1)) * x;
		ray.ray_dir.x = (player->dir.x + player->plane.x)
			- (player->plane.x * ray.camerax);
		ray.ray_dir.y = (player->dir.y + player->plane.y)
			-(player->plane.y * ray.camerax);
		dda = init_dda(*player, ray.ray_dir);
		ray.wall_dist = get_wall_dist(*player, ray.ray_dir, &dda, map);
		set_ray_draw_pos(&ray);
		rtex = set_render_texture(*player, ray, dda.side, textures);
		draw_wall(ray, rtex, x, buffer);
		x++;
	}
}

void	main_hook(void *param)
{
	t_vars	*vars;

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		side_step(&vars->player, vars->map, 1);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		side_step(&vars->player, vars->map, 0);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		move(&vars->player, vars->map, 1);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		move(&vars->player, vars->map, 0);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotate(&vars->player, vars->player.rot_speed, 1);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotate(&vars->player, vars->player.rot_speed, 0);
	init_buffer(vars->buffer);
	update_buffer(&vars->player, vars->map, vars->textures, vars->buffer);
	draw_buffer(vars->game, vars->buffer);
	vars->player.move_speed = vars->mlx->delta_time * 5.0;
	vars->player.rot_speed = vars->mlx->delta_time * 3.0;
}

int	main(int argc, const char *argv[])
{
	t_vars	vars;
	t_bg	bg;

	if (argc > 2)
	{
		printf("Error\nToo many arguments\n");
		exit(1);
	}
	if (parse_file(&vars, argv[1], &bg))
		exit(1);
	find_pos(&vars, vars.map);
	init_orientation(&vars);
	display_background(vars.mlx, bg);
	vars.game = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(vars.mlx, vars.game, 0, 0);
	update_buffer(&vars.player, vars.map, vars.textures, vars.buffer);
	mlx_loop_hook(vars.mlx, main_hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	free_2d_array(vars.map);
	free(vars.buffer);
	return (EXIT_SUCCESS);
}
