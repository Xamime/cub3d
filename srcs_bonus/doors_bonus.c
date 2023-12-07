/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:42:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/07 13:23:02 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

double	wall_hitpos(double player_pos, double side_dist, double ray_dir)
{
	double	hitpos;

	hitpos = player_pos + side_dist * ray_dir;
	hitpos -= floor(hitpos);
	hitpos = 1.0f - hitpos;
	return (hitpos);
}

static void	init_next(t_dda *dda, int *next_side, double *next_side_dist)
{
	if (dda->side_dist.x < dda->side_dist.y)
	{
		*next_side = 0;
		*next_side_dist = dda->side_dist.x;
		*next_side_dist += dda->delta_dist.x;
	}
	else
	{
		*next_side = 1;
		*next_side_dist = dda->side_dist.y;
		*next_side_dist += dda->delta_dist.y;
	}
}

static double	init_wall_y(t_dda *dda, t_player player, t_fpoint ray_dir, int door_axis)
{
	double	wall_y;
	double	side_dist;

	if (door_axis == 1)
	{
		side_dist = dda->side_dist.x;
		if (dda->side != door_axis)
			side_dist -= dda->delta_dist.x;
		wall_y = wall_hitpos(player.y, side_dist, ray_dir.y);
	}
	else
	{
		side_dist = dda->side_dist.y;
		if (dda->side != door_axis)
			side_dist -= dda->delta_dist.y;
		wall_y = wall_hitpos(player.x, side_dist, ray_dir.x);
	}
	return (wall_y);
}

int	collide_with_door(t_dda *dda, t_player player, t_fpoint ray_dir)
{
	t_door_collision	dc;

	dc.door_y = 0.5f;
	dc.door_axis = 1;
	if (dda->hit->orientation == WE)
		dc.door_axis = 0;
	if (dc.door_axis == 1)
		dc.ray_dir = ray_dir.y;
	else
		dc.ray_dir = ray_dir.x;
	init_next(dda, &dc.next_side, &dc.next_side_dist);
	dc.wall_y = init_wall_y(dda, player, ray_dir, dc.door_axis);
	if (dc.door_axis == 1)
		dc.door_x = wall_hitpos(player.x,
			dda->side_dist.y - dda->delta_dist.y / 2, ray_dir.x);
	else
		dc.door_x = wall_hitpos(player.y,
			dda->side_dist.x - dda->delta_dist.x / 2, ray_dir.y);
	dc.door_x = 1.0f - dc.door_x;
	return (check_all_cases(&dc, dda, player, ray_dir));
}
