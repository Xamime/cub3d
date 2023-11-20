/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 02:00:39 by max               #+#    #+#             */
/*   Updated: 2023/11/20 16:12:21 by jfarkas          ###   ########.fr       */
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
	player->has_moved = 1;
	// printf("dir.x %f, dir.x  %f,  planex  %f, camerax %f\n", player->dir.x, player->dir.x, player->plane.x, ray->camerax);
	// printf("dir.y %f, dir.y  %f,  planey  %f\n", player->dir.y, player->dir.y, player->plane.y);
	// printf("x = %f, y = %f, side_dist.x = %f, side_dist.y = %f\n", player->x , player->y, dda->side_dist.x, dda->side_dist.y);
	// printf("deltax %f  deltay %f\n\n", dda->delta_dist.x, dda->delta_dist.y);
}

void	rotate_right(t_player *player, double speed)
{
	double oldDirX = player->dir.x;
    player->dir.x = player->dir.x * cos(speed) - player->dir.y * sin(speed);
    player->dir.y = oldDirX * sin(speed) + player->dir.y * cos(speed);
    double oldPlaneX = player->plane.x;
    player->plane.x = player->plane.x * cos(speed) - player->plane.y * sin(speed);
    player->plane.y = oldPlaneX * sin(speed) + player->plane.y * cos(speed);
	player->has_moved = 1;
	// printf("dir.x %f, dir.x  %f,  planex  %f, camerax %f\n", player->dir.x, player->dir.x, player->plane.x, ray->camerax);
	// printf("dir.y %f, dir.y  %f,  planey  %f\n", player->dir.y, player->dir.y, player->plane.y);
	// printf("x = %f, y = %f, side_dist.x = %f, side_dist.y = %f\n", player->x , player->y, dda->side_dist.x, dda->side_dist.y);
	// printf("deltax %f  deltay %f\n\n", dda->delta_dist.x, dda->delta_dist.y);
}

void	ft_up(t_player *player, t_object **map)
{
	t_object	obj_x;
	t_object	obj_y;

	obj_x = map[(int)((player->y ))][(int)(player->x + player->dir.x * player->movespeed)];
	obj_y = map[(int)((player->y ) + player->dir.y * player->movespeed)][(int)(player->x)];
	if (obj_x.type != '1' || (obj_x.type == 'D' && obj_x.mode != 0))
		player->x += player->dir.x * player->movespeed;
	if (obj_y.type != '1' || (obj_x.type == 'D' && obj_x.mode != 0))
		player->y += player->dir.y * player->movespeed;
	player->has_moved = 1;
}

void	ft_down(t_player *player, t_object **map)
{
	t_object	obj_x;
	t_object	obj_y;

	obj_x = map[(int)((player->y ))][(int)(player->x - player->dir.x * player->movespeed)];
	obj_y = map[(int)((player->y ) - player->dir.y * player->movespeed)][(int)(player->x)];
	if (obj_x.type != '1')
		player->x -= player->dir.x * player->movespeed;
	if (obj_y.type != '1')
		player->y -= player->dir.y * player->movespeed;
	player->has_moved = 1;
}

void	right_step(t_player *player, t_object **map)
{
	t_object	obj_x;
	t_object	obj_y;

	obj_x = map[(int)((player->y ))][(int)(player->x - player->plane.x * player->movespeed)];
	obj_y = map[(int)((player->y ) - player->plane.y * player->movespeed)][(int)(player->x)];
	if (obj_x.type != '1')
		player->x -= player->plane.x * player->movespeed;
	if (obj_y.type != '1')
		player->y -= player->plane.y * player->movespeed;
	player->has_moved = 1;
}

void	left_step(t_player *player, t_object **map)
{
	t_object	obj_x;
	t_object	obj_y;

	obj_x = map[(int)((player->y ))][(int)(player->x + player->plane.x * player->movespeed)];
	obj_y = map[(int)((player->y ) + player->plane.y * player->movespeed)][(int)(player->x)];
	if (obj_x.type != '1')
		player->x += player->plane.x * player->movespeed;
	if (obj_y.type != '1')
		player->y += player->plane.y * player->movespeed;
	player->has_moved = 1;
}
