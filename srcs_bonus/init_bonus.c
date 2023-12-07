/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:45:25 by max               #+#    #+#             */
/*   Updated: 2023/12/07 16:41:28 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_buffer(uint32_t *buffer)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			buffer[y * WIDTH + x] = 0;
			x++;
		}
		y++;
	}
}

static void	init_images(mlx_image_t **game, mlx_image_t **minimap,
	mlx_image_t **crosshair, mlx_t *mlx)
{
	*game = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, *game, 0, 0);
	*crosshair = mlx_new_image(mlx, 18, 18);
	mlx_image_to_window(mlx, *crosshair, WIDTH / 2 - 9, HEIGHT / 2 - 9);
	*minimap = mlx_new_image(mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	mlx_image_to_window(mlx, *minimap, WIDTH - MINIMAP_SIZE, HEIGHT - MINIMAP_SIZE);
}

static void	init_orientation_NS(t_player *player)
{
	if (player->orientation == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = -0.5;
		player->plane.y = 0;
	}
	else if (player->orientation == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = 0.5;
		player->plane.y = 0;
	}
}

static void	init_orientation_WE(t_player *player)
{
	if (player->orientation == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -0.5;
	}
	else if (player->orientation == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = 0.5;
	}
}

void	init(t_vars *vars, t_bg *bg)
{
	init_objects(vars, vars->map);
	if (vars->player.orientation == 'N' || vars->player.orientation == 'S')
		init_orientation_NS(&vars->player);
	else
		init_orientation_WE(&vars->player);
	init_vars(vars);
	display_background(vars->mlx, *bg);
	init_images(&vars->game, &vars->minimap, &vars->crosshair, vars->mlx);
	init_buffer(vars->buffer);
}
