/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 02:00:39 by max               #+#    #+#             */
/*   Updated: 2023/12/07 02:07:17 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	rotate(t_player *player, double speed)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_s;
	double	sin_s;

	cos_s = cos(speed);
	sin_s = sin(speed);
	old_dir_x = player->dir.x;
	old_plane_x = player->plane.x;
	player->dir.x = player->dir.x * cos_s - player->dir.y * sin_s;
	player->dir.y = old_dir_x * sin_s + player->dir.y * cos_s;
	player->plane.x = player->plane.x * cos_s - player->plane.y * sin_s;
	player->plane.y = old_plane_x * sin_s + player->plane.y * cos_s;
}

static int	player_can_go_through_door(t_object obj)
{
	if (obj.type == 'D')
	{
		if (obj.orientation == NS && obj.mode <= 0.001f)
			return (1);
		else if (obj.orientation == WE && obj.mode <= 0.001f)
			return (1);
	}
	return (0);
}

static void	init_next(t_player *player,
		double *next_x, double *next_y, int dir)
{
	if (dir == UP || dir == DOWN)
	{
		*next_x = player->dir.x * player->move_speed;
		*next_y = player->dir.y * player->move_speed;
	}
	else
	{
		*next_x = player->plane.x * player->move_speed;
		*next_y = player->plane.y * player->move_speed;
	}
	if (dir == DOWN || dir == RIGHT)
	{
		*next_x *= -1.0f;
		*next_y *= -1.0f;
	}
}

void	move(t_player *player, t_object **map, int dir)
{
	t_object	obj_x;
	t_object	obj_y;
	double		next_x;
	double		next_y;

	init_next(player, &next_x, &next_y, dir);
	obj_x = map[(int)(player->y)][(int)(player->x + next_x)];
	obj_y = map[(int)(player->y + next_y)][(int)(player->x)];
	if (obj_x.type == '0' || player_can_go_through_door(obj_x))
		player->x += next_x;
	if (obj_y.type == '0' || player_can_go_through_door(obj_y))
		player->y += next_y;
}
