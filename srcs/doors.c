/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:42:39 by jfarkas           #+#    #+#             */
/*   Updated: 2023/11/18 04:05:10 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_next(t_dda *dda, t_fpoint *side_dist, int *next_side, double *next_side_dist)
{
	if (side_dist->x < side_dist->y)
	{
		*next_side = 0;
		*next_side_dist = side_dist->x;
		*next_side_dist += dda->delta_dist.x;
	}
	else
	{
		*next_side = 1;
		*next_side_dist = side_dist->y;
		*next_side_dist += dda->delta_dist.y;
	}
}

double	init_wallY(double player_pos, double side_dist, double ray_dir)
{
	double	wallY;

	wallY = player_pos + side_dist * ray_dir;
	wallY -= floor(wallY);
	wallY = 1.0f - wallY;
	return (wallY);
}

int	collide_with_door(t_dda *dda, t_fpoint *side_dist, t_object **map, t_player player, t_fpoint ray_dir)
{
	int		next_side;
	double	next_side_dist;
	double	wallX;
	double	next_wallX;
	double	wallY;
	double	next_wallY;

	int		door_axis = 1;
	int		not_door_axis = 0;

	double	threshold = 0.5f;
	double	rayd;

	if (door_axis == 1)
		rayd = ray_dir.y;
	else
		rayd = ray_dir.x;

	init_next(dda, side_dist, &next_side, &next_side_dist);

	if (door_axis == 1)
	{
		next_wallX = init_wallY(player.x, side_dist->y, ray_dir.x);
		wallY = init_wallY(player.y, side_dist->x, ray_dir.y);
	}
	else
		wallY = init_wallY(player.x, side_dist->y, ray_dir.x);
	if (dda->side == not_door_axis && door_axis == 1)
		wallY = init_wallY(player.y, side_dist->x - dda->delta_dist.x, ray_dir.y);
	else if (dda->side == not_door_axis && door_axis == 0)
		wallY = init_wallY(player.x, side_dist->y - dda->delta_dist.y, ray_dir.x);

	wallX = init_wallY(player.x, side_dist->y - dda->delta_dist.y, ray_dir.x);
	// wallY += 0.25f;
	// printf("side : %d\n", dda->side);
	// printf("side : %d, next_side : %d\n", dda->side, next_side);

	// printf("raw X : %d, raw next X : %d\n", (int)(side_dist->x - dda->delta_dist.x), (int)side_dist->x);
	// printf("wallX : %f, next wallX : %f\n", wallX, next_wallX);

	double	doorX = init_wallY(player.x, side_dist->y - dda->delta_dist.y / 2, ray_dir.x);

	// printf("doorX : %f\n", doorX);
	if (doorX > 0.5f - player.door_status && doorX < 0.5f + player.door_status)
		return (0);
	// ray enters in the NS axis and exits in the NS axis
	if (dda->side == door_axis && next_side == door_axis)
	{
		// if (wallX < 0.5f + lol && wallX > 0.5f - lol && next_wallX < 0.5f + lol && next_wallX > 0.5f - lol)
			// return (0);
		return (1);
	}
	// ray enters in the EW axis and exits in the EW axis and on the same side
	if (dda->side == not_door_axis && next_side == not_door_axis)
	{
		if (door_axis == 1)
			next_wallY = init_wallY(player.y, side_dist->x, ray_dir.y);
		else
			next_wallY = init_wallY(player.x, side_dist->y, ray_dir.x);
		if (wallY < threshold && next_wallY < threshold)
			return (0);
		else if (wallY > threshold && next_wallY > threshold)
			return (0);
	}

	// ray enters SOUTH, exits either EAST or WEST
	if (dda->side == door_axis && rayd < 0)
	{
		if (next_side == not_door_axis && wallY > threshold)
			return (1);
	}
	// ray enter NORTH, exits either EAST or WEST
	else if (dda->side == door_axis && rayd > 0)
	{
		if (next_side == not_door_axis && wallY < threshold)
			return (1);
	}

	// ray enters either SOUTH EAST or SOUTH WEST
	if (dda->side == not_door_axis && rayd < 0)
	{
		// printf("(dda) wallY : %f, wall_dist : %f\n", wallY, side_dist->x - dda->delta_dist.x / 2);
		if ((wallY < threshold && next_side == door_axis) || (next_side == not_door_axis && next_wallY > threshold))
		{
			dda->side = door_axis;
			return (1);
		}
	}
	// ray enters either NORTH EAST or NORTH WEST
	if (dda->side == not_door_axis && rayd > 0)
	{
		// printf("(dda) wallY : %f, wall_dist : %f\n", wallY, side_dist->x - dda->delta_dist.x / 2);
		if ((wallY > threshold && next_side == door_axis) || (next_side == not_door_axis && next_wallY < threshold))
		{
			dda->side = door_axis;
			return (1);
		}
	}
	// printf("is not door, wallY : %f\n", wallY);
	return (0);
}
