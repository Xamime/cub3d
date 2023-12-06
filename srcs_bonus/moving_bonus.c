/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 02:00:39 by max               #+#    #+#             */
/*   Updated: 2023/12/06 20:15:42 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

// a reduire

void	rotate_left(t_player *player, double speed)
{
	double oldDirX = player->dir.x;
    player->dir.x = player->dir.x * cos(-(speed)) - player->dir.y * sin(-(speed));
    player->dir.y = oldDirX * sin(-(speed)) + player->dir.y * cos(-(speed));
    double oldPlaneX = player->plane.x;
    player->plane.x = player->plane.x * cos(-(speed)) - player->plane.y * sin(-(speed));
    player->plane.y = oldPlaneX * sin(-(speed)) + player->plane.y * cos(-(speed));
}

void	rotate_right(t_player *player, double speed)
{
	double oldDirX = player->dir.x;
    player->dir.x = player->dir.x * cos(speed) - player->dir.y * sin(speed);
    player->dir.y = oldDirX * sin(speed) + player->dir.y * cos(speed);
    double oldPlaneX = player->plane.x;
    player->plane.x = player->plane.x * cos(speed) - player->plane.y * sin(speed);
    player->plane.y = oldPlaneX * sin(speed) + player->plane.y * cos(speed);
}

static void	init_next(t_player *player, double *next_x, double *next_y, int dir)
{
	if (dir == UP || dir == DOWN)
	{
		*next_x = player->dir.x * player->movespeed;
		*next_y = player->dir.y * player->movespeed;
	}
	else
	{
		*next_x = player->plane.x * player->movespeed;
		*next_y = player->plane.y * player->movespeed;
	}
	if (dir == DOWN || dir == RIGHT)
	{
		*next_x *= -1.0f;
		*next_y *= -1.0f;
	}
}

int	player_can_go_through_door(t_object obj)
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
