/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 02:00:39 by max               #+#    #+#             */
/*   Updated: 2023/12/05 18:21:25 by jfarkas          ###   ########.fr       */
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

void	ft_up(t_player *player, t_object **map)
{
	t_object	obj_x;
	t_object	obj_y;

	obj_x = map[(int)((player->y ))][(int)(player->x + player->dir.x * player->movespeed)];
	obj_y = map[(int)((player->y ) + player->dir.y * player->movespeed)][(int)(player->x)];
	if (obj_x.type == '0' || (obj_x.type == 'D' && obj_x.mode <= 0.0f))
		player->x += player->dir.x * player->movespeed;
	if (obj_y.type == '0' || (obj_y.type == 'D' && obj_y.mode <= 0.0f))
		player->y += player->dir.y * player->movespeed;
}

void	ft_down(t_player *player, t_object **map)
{
	t_object	obj_x;
	t_object	obj_y;

	obj_x = map[(int)((player->y ))][(int)(player->x - player->dir.x * player->movespeed)];
	obj_y = map[(int)((player->y ) - player->dir.y * player->movespeed)][(int)(player->x)];
	if (obj_x.type == '0' || (obj_x.type == 'D' && obj_x.mode <= 0.0f))
		player->x -= player->dir.x * player->movespeed;
	if (obj_y.type == '0' || (obj_y.type == 'D' && obj_y.mode <= 0.0f))
		player->y -= player->dir.y * player->movespeed;
}

void	right_step(t_player *player, t_object **map)
{
	t_object	obj_x;
	t_object	obj_y;

	obj_x = map[(int)((player->y ))][(int)(player->x - player->plane.x * player->movespeed)];
	obj_y = map[(int)((player->y ) - player->plane.y * player->movespeed)][(int)(player->x)];
	if (obj_x.type == '0' || (obj_x.type == 'D' && obj_x.mode <= 0.0f))
		player->x -= player->plane.x * player->movespeed;
	if (obj_y.type == '0' || (obj_y.type == 'D' && obj_y.mode <= 0.0f))
		player->y -= player->plane.y * player->movespeed;
}

void	left_step(t_player *player, t_object **map)
{
	t_object	obj_x;
	t_object	obj_y;

	obj_x = map[(int)((player->y ))][(int)(player->x + player->plane.x * player->movespeed)];
	obj_y = map[(int)((player->y ) + player->plane.y * player->movespeed)][(int)(player->x)];
	if (obj_x.type == '0' || (obj_x.type == 'D' && obj_x.mode <= 0.0f))
		player->x += player->plane.x * player->movespeed;
	if (obj_y.type == '0' || (obj_y.type == 'D' && obj_y.mode <= 0.0f))
		player->y += player->plane.y * player->movespeed;
}
