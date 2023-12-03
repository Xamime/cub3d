/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/12/03 15:01:34 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_ray	update_buffer(t_player *player, char **map,
	mlx_image_t *textures[4], uint32_t *buffer)
{
	t_dda			dda;
	t_ray			ray;
	t_render_tex	rtex;
	int				x;

	x = 0;
	while (x < WIDTH)
	{
		// pas droit quand different de 2.0 ?
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
	return (ray);
}

void	hook_again(t_vars *vars, t_ray ray)
{
	init(vars);
	ray = update_buffer(&vars->player,
			vars->map, vars->textures, vars->buffer);
	draw_buffer(vars, vars->game, vars->buffer);
	vars->player.movespeed = vars->mlx->delta_time * 5.0;
	vars->player.rotspeed = vars->mlx->delta_time * 3.0;
	vars->player.has_moved = 0;
}

void	ft_hook(void *param)
{
	t_ray	ray;
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
		rotate(&vars->player, vars->player.rotspeed, 1);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotate(&vars->player, vars->player.rotspeed, 0);
	hook_again(vars, ray);
}

int	start_loop(t_vars *vars, const char *path)
{
	t_bgrd	bgrd;

	if (parse_file(vars, path, &bgrd))
		exit(1);
	find_pos(vars, vars->map);
	init_orientation(vars);
	display_background(vars->mlx, bgrd);
	vars->game = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->instance = mlx_image_to_window(vars->mlx, vars->game, 0, 0);
	update_buffer(&vars->player, vars->map, vars->textures, vars->buffer);
	mlx_loop_hook(vars->mlx, ft_hook, vars);
	mlx_loop(vars->mlx);
	return (EXIT_SUCCESS);
}

int	main(int32_t argc, const char *argv[])
{
	t_vars	vars;
	int		fd;

	(void)argc;
	start_loop(&vars, argv[1]);
	mlx_terminate(vars.mlx);
	free_map(vars.map);
	free(vars.buffer);
	return (EXIT_SUCCESS);
}
