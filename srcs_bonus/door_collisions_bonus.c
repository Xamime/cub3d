/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_collisions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:19:37 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/07 15:16:10 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	ray_same_door_side_wall_axis(t_door_collision *dc, t_dda *dda, t_player player, t_fpoint ray_dir)
{
	if (dda->side != dc->door_axis && dc->next_side != dc->door_axis)
	{
		if (dc->door_axis == 1)
			dc->next_wall_y = wall_hitpos(player.y, dda->side_dist.x, ray_dir.y);
		else
			dc->next_wall_y = wall_hitpos(player.x, dda->side_dist.y, ray_dir.x);
		if (dc->wall_y < dc->door_y && dc->next_wall_y < dc->door_y)
			return (1);
		else if (dc->wall_y > dc->door_y && dc->next_wall_y > dc->door_y)
			return (1);
	}
	return (0);
}

static int	ray_door_axis_to_wall_axis(t_door_collision *dc, t_dda *dda)
{
	if (dda->side == dc->door_axis && dc->ray_dir < 0)
	{
		if (dc->next_side != dc->door_axis && dc->wall_y > dc->door_y)
			return (1);
	}
	else if (dda->side == dc->door_axis && dc->ray_dir > 0)
	{
		if (dc->next_side != dc->door_axis && dc->wall_y < dc->door_y)
			return (1);
	}
	return (0);
}

static int	ray_different_door_side_wall_axis(t_door_collision *dc, t_dda *dda)
{
	if (dda->side != dc->door_axis && dc->ray_dir < 0)
	{
		if ((dc->wall_y < dc->door_y && dc->next_side == dc->door_axis)
			|| (dc->next_side != dc->door_axis && dc->next_wall_y > dc->door_y))
		{
			dda->side = dc->door_axis;
			return (1);
		}
	}
	if (dda->side != dc->door_axis && dc->ray_dir > 0)
	{
		if ((dc->wall_y > dc->door_y && dc->next_side == dc->door_axis)
			|| (dc->next_side != dc->door_axis && dc->next_wall_y < dc->door_y))
		{
			dda->side = dc->door_axis;
			return (1);
		}
	}
	return (0);
}

int	check_all_cases(t_door_collision *dc, t_dda *dda, t_player player, t_fpoint ray_dir)
{
	if (dc->door_x > dda->hit->mode)
		return (0);
	if (dda->side == dc->door_axis && dc->next_side == dc->door_axis)
		return (1);
	if (ray_same_door_side_wall_axis(dc, dda, player, ray_dir))
		return (0);
	if (ray_door_axis_to_wall_axis(dc, dda))
		return (1);
	if (ray_different_door_side_wall_axis(dc, dda))
		return (1);
	return (0);
}
