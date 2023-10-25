/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:40:51 by jfarkas           #+#    #+#             */
/*   Updated: 2023/10/25 09:12:44 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

double	get_wall_dist(t_player player, t_fpoint ray_dir, t_dda *dda, char **map)
{
	t_fpoint	side_dist;

	side_dist.x = init_side_dist(ray_dir.x, player.x, dda->map.x, dda->delta_dist.x);
	side_dist.y = init_side_dist(ray_dir.y, player.y, dda->map.y, dda->delta_dist.y);
	while (map[dda->map.y][dda->map.x] != '1')
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
