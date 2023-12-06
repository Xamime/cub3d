/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:42:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/06 22:35:57 by jfarkas          ###   ########.fr       */
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

void	init_next(t_dda *dda, int *next_side, double *next_side_dist)
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

double	init_wall_y(t_dda *dda, t_player player, t_fpoint ray_dir, int door_axis)
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

int	collide_with_door(t_dda *dda, t_object **map, t_player player, t_fpoint ray_dir)
{
	int		next_side;
	double	next_side_dist;
	double	door_x;
	double	wallY;
	double	next_wallY;

	double	door_y = 0.5f;
	double	rayd;
	(void)map;

	int		door_axis;
	int		wall_axis;

	door_axis = 1;
	wall_axis = 0;
	if (dda->hit->orientation == WE)
	{
		door_axis = 0;
		wall_axis = 1;
	}

	if (door_axis == 1)
		rayd = ray_dir.y;
	else
		rayd = ray_dir.x;

	init_next(dda, &next_side, &next_side_dist);

	wallY = init_wall_y(dda, player, ray_dir, door_axis);
	if (door_axis == 1)
		door_x = wall_hitpos(player.x, dda->side_dist.y - dda->delta_dist.y / 2, ray_dir.x);
	else
		door_x = wall_hitpos(player.y, dda->side_dist.x - dda->delta_dist.x / 2, ray_dir.y);
	door_x = 1.0f - door_x;

	// if (door_axis == 1)
	// {
	// 	door_x = wall_hitpos(player.x, dda->side_dist.y - dda->delta_dist.y / 2, ray_dir.x);
	// 	wallY = wall_hitpos(player.y, dda->side_dist.x, ray_dir.y);
	// }
	// else
	// {
	// 	door_x = wall_hitpos(player.y, dda->side_dist.x - dda->delta_dist.x / 2, ray_dir.y);
	// 	wallY = wall_hitpos(player.x, dda->side_dist.y, ray_dir.x);
	// }
	// if (dda->side == wall_axis && door_axis == 1)
	// 	wallY = wall_hitpos(player.y, dda->side_dist.x - dda->delta_dist.x, ray_dir.y);
	// else if (dda->side == wall_axis && door_axis == 0)
	// 	wallY = wall_hitpos(player.x, dda->side_dist.y - dda->delta_dist.y, ray_dir.x);

	// wallY += 0.25f;
	// printf("side : %d\n", dda->side);
	// printf("side : %d, next_side : %d\n", dda->side, next_side);

	// printf("raw X : %d, raw next X : %d\n", (int)(dda->side_dist.x - dda->delta_dist.x), (int)dda->side_dist.x);
	// printf("wallX : %f, next wallX : %f\n", wallX, next_wallX);

	// printf("door_x : %f\n", door_x);
	if (door_x > dda->hit->mode)
		return (0);

	// ray enters in the NS axis and exits in the NS axis
	if (dda->side == door_axis && next_side == door_axis)
	{
		// if (wallX < 0.5f + lol && wallX > 0.5f - lol && next_wallX < 0.5f + lol && next_wallX > 0.5f - lol)
		// 	return (0);
		return (1);
	}
	// ray enters in the EW axis and exits in the EW axis and on the same side
	if (dda->side == wall_axis && next_side == wall_axis)
	{
		if (door_axis == 1)
			next_wallY = wall_hitpos(player.y, dda->side_dist.x, ray_dir.y);
		else
			next_wallY = wall_hitpos(player.x, dda->side_dist.y, ray_dir.x);
		if (wallY < door_y && next_wallY < door_y)
			return (0);
		else if (wallY > door_y && next_wallY > door_y)
			return (0);
	}

	// ray enters SOUTH, exits either EAST or WEST
	if (dda->side == door_axis && rayd < 0)
	{
		if (next_side == wall_axis && wallY > door_y)
			return (1);
	}
	// ray enter NORTH, exits either EAST or WEST
	else if (dda->side == door_axis && rayd > 0)
	{
		if (next_side == wall_axis && wallY < door_y)
			return (1);
	}

	// ray enters either SOUTH EAST or SOUTH WEST
	if (dda->side == wall_axis && rayd < 0)
	{
		// printf("(dda) wallY : %f, wall_dist : %f\n", wallY, dda->side_dist.x - dda->delta_dist.x / 2);
		if ((wallY < door_y && next_side == door_axis) || (next_side == wall_axis && next_wallY > door_y))
		{
			dda->side = door_axis;
			return (1);
		}
	}
	// ray enters either NORTH EAST or NORTH WEST
	if (dda->side == wall_axis && rayd > 0)
	{
		// printf("(dda) wallY : %f, wall_dist : %f\n", wallY, dda->side_dist.x - dda->delta_dist.x / 2);
		if ((wallY > door_y && next_side == door_axis) || (next_side == wall_axis && next_wallY < door_y))
		{
			dda->side = door_axis;
			return (1);
		}
	}
	// printf("is not door, wallY : %f\n", wallY);
	return (0);
}
