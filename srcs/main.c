/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/10/22 16:12:41 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	display_fps(t_vars *vars)
{
	// printf("fps = %f\n", 1.0 / vars->mlx->delta_time);
	char	*str = NULL;
	char	*tmp;
	str = malloc(sizeof(char) * 20);
	float_to_char((1.0 / vars->mlx->delta_time), str, 1);
	tmp = str;
	str = ft_strjoin(str, " FPS");
	free(tmp);
	// vars->instance2 = mlx_put_string(vars->mlx, str, 0, 20);
	mlx_set_window_title(vars->mlx, str);
	free(str);
}

void	 update_buffer(t_player *player, char **map, mlx_image_t *textures[4], uint32_t *buffer)
{
	t_dda			dda;
	t_ray			ray;
	t_render_tex	rtex;

	for (int x = 0; x < WIDTH; x++)
	{
		ray.camerax = (2.0f / (double)(WIDTH - 1)) * x; // pas droit quand different de 2.0 ?
		ray.ray_dir.x = (player->dir.x - player->plane.x) + (player->plane.x * ray.camerax);
		ray.ray_dir.y = (player->dir.y - player->plane.y) + (player->plane.y * ray.camerax);
		dda = init_dda(*player, ray.ray_dir);
		ray.wall_dist = get_wall_dist(*player, ray.ray_dir, &dda, map);
		set_ray_draw_pos(&ray);
		draw_floor(buffer, x, ray.drawend);
		draw_ceiling(buffer, x, ray.drawstart);
		rtex = set_render_texture(*player, ray, dda.side, textures);
		draw_wall(ray, rtex, x, buffer);
	}
}

void ft_hook(void* param)
{
	t_vars *vars  = param;

	//ft_draw_pixels_grid(vars);
	//ft_draw_pixels_player(vars);
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
		rotate_left(&vars->player);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotate_right(&vars->player);
	if (vars->player.has_moved)
	{
		init(vars);
		update_buffer(&vars->player, vars->map, vars->textures, vars->buffer);
		draw_buffer(vars, vars->game, vars->buffer);
		vars->player.movespeed = vars->mlx->delta_time * 5.0;
		vars->player.rotspeed = vars->mlx->delta_time * 3.0;
		// ft_display_rays(vars, ray);
		display_fps(vars);
		vars->player.has_moved = 0;
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
	update_buffer(&vars->player, vars->map, vars->textures, vars->buffer);
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