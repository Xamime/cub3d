/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/12/07 19:51:56 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	update_buffer(t_player *player, t_object **map,
	mlx_image_t *textures[4], uint32_t *buffer)
{
	t_dda			dda;
	t_ray			ray;
	t_rtex			rtex;
	int				x;

	x = 0;
	while (x < WIDTH)
	{
		ray.camerax = (2.0f / (double)(WIDTH - 1)) * x;
		ray.ray_dir.x = (player->dir.x + player->plane.x)
			- (player->plane.x * ray.camerax);
		ray.ray_dir.y = (player->dir.y + player->plane.y)
			- (player->plane.y * ray.camerax);
		dda = init_dda(*player, ray.ray_dir);
		ray.wall_dist = get_wall_dist(player, ray.ray_dir, &dda, map);
		if (x == WIDTH / 2 && !player->door_opening && !player->door_closing)
			player->aimed_obj = dda.first_door;
		set_ray_draw_pos(&ray);
		rtex = set_render_texture(*player, ray, &dda, textures);
		draw_wall(ray, rtex, x, buffer);
		x++;
	}
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
	init(&vars, &bg);
	update_buffer(&vars.player, vars.map, vars.textures, vars.buffer);
	mlx_loop_hook(vars.mlx, main_hook, &vars);
	mlx_set_cursor_mode(vars.mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(vars.mlx, WIDTH / 2, HEIGHT / 2);
	mlx_cursor_hook(vars.mlx, cursor_hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	free_map(vars.map);
	free(vars.buffer);
	return (EXIT_SUCCESS);
}
