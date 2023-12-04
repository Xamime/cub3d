/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:45:25 by max               #+#    #+#             */
/*   Updated: 2023/12/04 03:43:51 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_buffer(t_vars *vars)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			vars->buffer[y * WIDTH + x] = 0;
			x++;
		}
		y++;
	}
}

static void	init_orientation_w_s(t_vars *vars)
{
	if (vars->player.orientation == 'W')
	{
		vars->player.dir.x = -1;
		vars->player.dir.y = 0;
		vars->player.plane.x = 0;
		vars->player.plane.y = 0.5;
	}
	else if (vars->player.orientation == 'S')
	{
		vars->player.dir.x = 0;
		vars->player.dir.y = 1;
		vars->player.plane.x = 0.5;
		vars->player.plane.y = 0;
	}
}

void	init_orientation(t_vars *vars)
{
	if (vars->player.orientation == 'N')
	{
		vars->player.dir.x = 0;
		vars->player.dir.y = -1;
		vars->player.plane.x = -0.5;
		vars->player.plane.y = 0;
	}
	else if (vars->player.orientation == 'E')
	{
		vars->player.dir.x = 1;
		vars->player.dir.y = 0;
		vars->player.plane.x = 0;
		vars->player.plane.y = -0.5;
	}
	else
		init_orientation_w_s(vars);
}

void	find_pos(t_vars *vars, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] && (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E'))
			{
				vars->player.x = j;
				vars->player.y = i;
				vars->player.orientation = map[i][j];
			}
			j++;
		}
		i++;
	}
}
