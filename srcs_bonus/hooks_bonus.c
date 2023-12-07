/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:17:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/07 18:49:35 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	door_hook(t_object **map, t_player *player,
	double *time, mlx_t *mlx)
{
	*time += mlx->delta_time;
	if (mlx_is_key_down(mlx, MLX_KEY_KP_4)
		&& player->aimed_obj
		&& !player->door_closing)
		player->door_opening = 1;
	else if (mlx_is_key_down(mlx, MLX_KEY_KP_6)
		&& player->aimed_obj
		&& !player->door_opening
		&& map[(int)player->y][(int)player->x].type != 'D')
		player->door_closing = 1;
	if (*time > 0.0125f && (player->door_opening
			|| player->door_closing))
		open_door(player, time);
}

static void	minimap_hook(double *case_size, mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_KP_ADD))
		*case_size *= 1.1f;
	if (mlx_is_key_down(mlx, MLX_KEY_KP_SUBTRACT))
	{
		if (*case_size > 1.0f)
			*case_size *= 0.9f;
	}
}

static void	move_hook(t_object **map, t_player *player, mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move(player, map, LEFT);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move(player, map, RIGHT);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move(player, map, UP);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move(player, map, DOWN);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate(player, -(player->rot_speed));
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate(player, player->rot_speed);
}

void	cursor_hook(double x, double y, void *param)
{
	t_vars	*vars;
	double	delta_x;

	vars = (t_vars *)param;
	(void)y;
	delta_x = x - WIDTH / 2;
	rotate(&vars->player, delta_x / 400);
	mlx_set_mouse_pos(vars->mlx, WIDTH / 2, HEIGHT / 2);
}

void	main_hook(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	move_hook(vars->map, &vars->player, vars->mlx);
	door_hook(vars->map, &vars->player, &vars->time, vars->mlx);
	minimap_hook(&vars->case_size, vars->mlx);
	init_buffer(vars->buffer);
	update_buffer(&vars->player, vars->map, vars->textures, vars->buffer);
	draw_buffer(vars->game, vars->buffer);
	draw_minimap(vars);
	draw_crosshair(vars->crosshair);
	vars->player.move_speed = vars->mlx->delta_time * 5.0;
	vars->player.rot_speed = vars->mlx->delta_time * 3.0;
}
