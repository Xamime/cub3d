/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 02:00:39 by max               #+#    #+#             */
/*   Updated: 2023/10/22 09:09:38 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// a reduire

void	rotate_left(t_player *player)
{
	double oldDirX = player->dir.x;
    player->dir.x = player->dir.x * cos(player->rotspeed) - player->dir.y * sin(player->rotspeed);
    player->dir.y = oldDirX * sin(player->rotspeed) + player->dir.y * cos(player->rotspeed);
    double oldPlaneX = player->plane.x;
    player->plane.x = player->plane.x * cos(player->rotspeed) - player->plane.y * sin(player->rotspeed);
    player->plane.y = oldPlaneX * sin(player->rotspeed) + player->plane.y * cos(player->rotspeed);
	player->has_moved = 1;
	// printf("dir.x %f, dir.x  %f,  planex  %f, camerax %f\n", player->dir.x, player->dir.x, player->plane.x, ray->camerax);
	// printf("dir.y %f, dir.y  %f,  planey  %f\n", player->dir.y, player->dir.y, player->plane.y);
	// printf("x = %f, y = %f, side_dist.x = %f, side_dist.y = %f\n", player->x , player->y, dda->side_dist.x, dda->side_dist.y);
	// printf("deltax %f  deltay %f\n\n", dda->delta_dist.x, dda->delta_dist.y);
}

void	rotate_right(t_player *player)
{
	double oldDirX = player->dir.x;
    player->dir.x = player->dir.x * cos(-(player->rotspeed)) - player->dir.y * sin(-(player->rotspeed));
    player->dir.y = oldDirX * sin(-(player->rotspeed)) + player->dir.y * cos(-(player->rotspeed));
    double oldPlaneX = player->plane.x;
    player->plane.x = player->plane.x * cos(-(player->rotspeed)) - player->plane.y * sin(-(player->rotspeed));
    player->plane.y = oldPlaneX * sin(-(player->rotspeed)) + player->plane.y * cos(-(player->rotspeed));
	player->has_moved = 1;
	// printf("dir.x %f, dir.x  %f,  planex  %f, camerax %f\n", player->dir.x, player->dir.x, player->plane.x, ray->camerax);
	// printf("dir.y %f, dir.y  %f,  planey  %f\n", player->dir.y, player->dir.y, player->plane.y);
	// printf("x = %f, y = %f, side_dist.x = %f, side_dist.y = %f\n", player->x , player->y, dda->side_dist.x, dda->side_dist.y);
	// printf("deltax %f  deltay %f\n\n", dda->delta_dist.x, dda->delta_dist.y);
}

void	ft_up(t_player *player, char **map)
{
	if(map[(int)((player->y ) + player->dir.y * player->movespeed)][(int)(player->x)] != '1')
		(player->y ) += player->dir.y * player->movespeed;
	if(map[(int)((player->y ))][(int)(player->x + player->dir.x * player->movespeed)] != '1')
		player->x += player->dir.x * player->movespeed;
	player->has_moved = 1;
	// printf("dir.x %f, dir.x  %f,  planex  %f, camerax %f\n", player->dir.x, player->dir.x, player->plane.x, ray->camerax);
	// printf("dir.y %f, dir.y  %f,  planey  %f\n", player->dir.y, player->dir.y, player->plane.y);
	// printf("x = %f, y = %f, side_dist.x = %f, side_dist.y = %f\n", player->x , player->y, dda->side_dist.x, dda->side_dist.y);
	// printf("deltax %f  deltay %f\n\n", dda->delta_dist.x, dda->delta_dist.y);
}

void	ft_down(t_player *player, char **map)
{
	if (map[(int)((player->y ) - player->dir.y * player->movespeed)][(int)(player->x)] != '1')
		(player->y ) -= player->dir.y * player->movespeed;
    if (map[(int)((player->y ))][(int)(player->x - player->dir.x * player->movespeed)] != '1')
		player->x -= player->dir.x * player->movespeed;
	player->has_moved = 1;
	// printf("x = %f, y = %f, side_dist.x = %f, side_dist.y = %f\n", player->x , player->y, dda->side_dist.x, dda->side_dist.y);
	// printf("dir.x %f, dir.x  %f,  planex  %f, camerax %f\n", player->dir.x, player->dir.x, player->plane.x, ray->camerax);
	// printf("dir.y %f, dir.y  %f,  planey  %f\n", player->dir.y, player->dir.y, player->plane.y);
	// printf("deltax %f  deltay %f\n\n", dda->delta_dist.x, dda->delta_dist.y);

}

void	right_step(t_player *player, char **map)
{
	if(map[(int)((player->y ) + player->plane.y * player->movespeed)][(int)(player->x)] != '1')
		(player->y ) += player->plane.y * player->movespeed;
    if(map[(int)((player->y ))][(int)(player->x + player->plane.x * player->movespeed)] != '1')
		player->x += player->plane.x * player->movespeed;
	player->has_moved = 1;
}

void	left_step(t_player *player, char **map)
{
	if (map[(int)((player->y ) - player->plane.y * player->movespeed)][(int)(player->x)] != '1')
		(player->y ) -= player->plane.y * player->movespeed;
    if (map[(int)((player->y ))][(int)(player->x - player->plane.x * player->movespeed)] != '1')
		player->x -= player->plane.x * player->movespeed;
	player->has_moved = 1;
}