/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:40:51 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/03 21:46:44 by mdesrose         ###   ########.fr       */
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

static double	init_side_dist(double ray_dir, double player_pos,
	int map_pos, double delta)
{
	if (ray_dir < 0)
		return ((player_pos - map_pos) * delta);
	else
		return ((map_pos + 1.0f - player_pos) * delta);
}

static void	dda_loop(t_dda *dda, char **map)
{
	while (map[dda->map.y][dda->map.x] != '1')
	{
		if (dda->side_dist.x < dda->side_dist.y)
		{
			dda->side = 0;
			dda->side_dist.x += dda->delta_dist.x;
			dda->map.x += dda->step.x;
		}
		else
		{
			dda->side = 1;
			dda->side_dist.y += dda->delta_dist.y;
			dda->map.y += dda->step.y;
		}
	}
}

double	get_wall_dist(t_player player, t_fpoint ray_dir, t_dda *dda, char **map)
{
	dda->side_dist.x = init_side_dist(ray_dir.x, player.x,
			dda->map.x, dda->delta_dist.x);
	dda->side_dist.y = init_side_dist(ray_dir.y, player.y,
			dda->map.y, dda->delta_dist.y);
	dda_loop(dda, map);
	if (dda->side == 0)
		return (dda->side_dist.x - dda->delta_dist.x);
	return (dda->side_dist.y - dda->delta_dist.y);
}

t_dda	init_dda(t_player player, t_fpoint ray_dir)
{
	t_dda	dda;

	dda.map.x = (int)(player.x);
	dda.map.y = (int)(player.y);
	dda.delta_dist.x = fabs(1 / ray_dir.x);
	dda.delta_dist.y = fabs(1 / ray_dir.y);
	dda.step.x = init_step(ray_dir.x);
	dda.step.y = init_step(ray_dir.y);
	return (dda);
}
