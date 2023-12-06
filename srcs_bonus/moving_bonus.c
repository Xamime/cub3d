/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 02:00:39 by max               #+#    #+#             */
/*   Updated: 2023/12/06 21:58:46 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	rotate_left(t_player *player, double speed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = player->dir.x;
	player->dir.x = player->dir.x * cos(-(speed))
		- player->dir.y * sin(-(speed));
	player->dir.y = olddirx * sin(-(speed)) + player->dir.y * cos(-(speed));
	oldplanex = player->plane.x;
	player->plane.x = player->plane.x * cos(-(speed))
		- player->plane.y * sin(-(speed));
	player->plane.y = oldplanex * sin(-(speed))
		+ player->plane.y * cos(-(speed));
}

void	rotate_right(t_player *player, double speed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = player->dir.x;
	player->dir.x = player->dir.x * cos(speed) - player->dir.y * sin(speed);
	player->dir.y = olddirx * sin(speed) + player->dir.y * cos(speed);
	oldplanex = player->plane.x;
	player->plane.x = player->plane.x * cos(speed)
		- player->plane.y * sin(speed);
	player->plane.y = oldplanex * sin(speed) + player->plane.y * cos(speed);
}

static void	init_next(t_player *player,
		double *next_x, double *next_y, int dir)
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

void	move(t_player *player, t_object **map, int dir)
{
	t_object	obj_x;
	t_object	obj_y;
	double		next_x;
	double		next_y;

	init_next(player, &next_x, &next_y, dir);
	obj_x = map[(int)(player->y)][(int)(player->x + next_x)];
	obj_y = map[(int)(player->y + next_y)][(int)(player->x)];
	if (obj_x.type == '0' || (obj_x.type == 'D'
			&& obj_x.mode <= player->x - (int)player->x))
		player->x += next_x;
	if (obj_y.type == '0' || (obj_y.type == 'D'
			&& obj_y.mode <= player->x - (int)player->x))
		player->y += next_y;
}
