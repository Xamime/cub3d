/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 02:00:39 by max               #+#    #+#             */
/*   Updated: 2023/12/03 21:31:24 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate(t_player *player, double speed, int left)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = player->dir.x;
	oldplane_x = player->plane.x;
	if (left == 1)
		speed *= -1;
	player->dir.x = player->dir.x * cos(speed) - player->dir.y * sin(speed);
	player->dir.y = olddir_x * sin(speed) + player->dir.y * cos(speed);
	player->plane.x = player->plane.x * cos(speed)
		- player->plane.y * sin(speed);
	player->plane.y = oldplane_x * sin(speed) + player->plane.y * cos(speed);
}

void	move(t_player *player, char **map, int up)
{
	if (up == 1)
	{
		if (map[(int)((player->y) + player->dir.y
				* player->movespeed)][(int)(player->x)] != '1')
			player->y += player->dir.y * player->movespeed;
		if (map[(int)((player->y))][(int)(player->x + player->dir.x
				* player->movespeed)] != '1')
			player->x += player->dir.x * player->movespeed;
	}
	else
	{
		if (map[(int)((player->y) - player->dir.y
				* player->movespeed)][(int)(player->x)] != '1')
			player->y -= player->dir.y * player->movespeed;
		if (map[(int)((player->y))][(int)(player->x - player->dir.x
				* player->movespeed)] != '1')
			player->x -= player->dir.x * player->movespeed;
	}
}

void	side_step(t_player *player, char **map, int left)
{
	if (left == 1)
	{
		if (map[(int)((player->y) + player->plane.y
				* player->movespeed)][(int)(player->x)] != '1')
			player->y += player->plane.y * player->movespeed;
		if (map[(int)(player->y)][(int)(player->x + player->plane.x *
				player->movespeed)] != '1')
			player->x += player->plane.x * player->movespeed;
	}
	else
	{
		if (map[(int)((player->y) - player->plane.y
				* player->movespeed)][(int)(player->x)] != '1')
			player->y -= player->plane.y * player->movespeed;
		if (map[(int)((player->y))][(int)(player->x - player->plane.x
				* player->movespeed)] != '1')
			player->x -= player->plane.x * player->movespeed;
	}
}
