/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 02:00:39 by max               #+#    #+#             */
/*   Updated: 2023/10/22 06:54:21 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    rotate_left(t_vars *vars, t_ray *ray)
{
	double oldDirX = ray->dir.x;
    ray->dir.x = ray->dir.x * cos(vars->player.rotspeed) - ray->dir.y * sin(vars->player.rotspeed);
    ray->dir.y = oldDirX * sin(vars->player.rotspeed) + ray->dir.y * cos(vars->player.rotspeed);
    double oldPlaneX = ray->plane.x;
    ray->plane.x = ray->plane.x * cos(vars->player.rotspeed) - ray->plane.y * sin(vars->player.rotspeed);
    ray->plane.y = oldPlaneX * sin(vars->player.rotspeed) + ray->plane.y * cos(vars->player.rotspeed);
	// printf("dir.x %f, dir.x  %f,  planex  %f, camerax %f\n", ray->dir.x, ray->dir.x, ray->plane.x, ray->camerax);
	// printf("dir.y %f, dir.y  %f,  planey  %f\n", ray->dir.y, ray->dir.y, ray->plane.y);
	// printf("x = %f, y = %f, side_dist.x = %f, side_dist.y = %f\n", vars->player.x , vars->player.y, dda->side_dist.x, dda->side_dist.y);
	// printf("deltax %f  deltay %f\n\n", dda->delta_dist.x, dda->delta_dist.y);
}

void    rotate_right(t_vars *vars, t_ray *ray)
{
		double oldDirX = ray->dir.x;
      ray->dir.x = ray->dir.x * cos(-(vars->player.rotspeed)) - ray->dir.y * sin(-(vars->player.rotspeed));
      ray->dir.y = oldDirX * sin(-(vars->player.rotspeed)) + ray->dir.y * cos(-(vars->player.rotspeed));
      double oldPlaneX = ray->plane.x;
      ray->plane.x = ray->plane.x * cos(-(vars->player.rotspeed)) - ray->plane.y * sin(-(vars->player.rotspeed));
      ray->plane.y = oldPlaneX * sin(-(vars->player.rotspeed)) + ray->plane.y * cos(-(vars->player.rotspeed));
	// printf("dir.x %f, dir.x  %f,  planex  %f, camerax %f\n", ray->dir.x, ray->dir.x, ray->plane.x, ray->camerax);
	// printf("dir.y %f, dir.y  %f,  planey  %f\n", ray->dir.y, ray->dir.y, ray->plane.y);
	// printf("x = %f, y = %f, side_dist.x = %f, side_dist.y = %f\n", vars->player.x , vars->player.y, dda->side_dist.x, dda->side_dist.y);
	// printf("deltax %f  deltay %f\n\n", dda->delta_dist.x, dda->delta_dist.y);
}

void	ft_up(t_vars *vars, t_ray *ray)
{
	if(vars->map[(int)((vars->player.y ) + ray->dir.y * vars->player.movespeed)][(int)(vars->player.x)] != '1')
		(vars->player.y ) += ray->dir.y * vars->player.movespeed;
    if(vars->map[(int)((vars->player.y ))][(int)(vars->player.x + ray->dir.x * vars->player.movespeed)] != '1')
		vars->player.x += ray->dir.x * vars->player.movespeed;
	// printf("dir.x %f, dir.x  %f,  planex  %f, camerax %f\n", ray->dir.x, ray->dir.x, ray->plane.x, ray->camerax);
	// printf("dir.y %f, dir.y  %f,  planey  %f\n", ray->dir.y, ray->dir.y, ray->plane.y);
	// printf("x = %f, y = %f, side_dist.x = %f, side_dist.y = %f\n", vars->player.x , vars->player.y, dda->side_dist.x, dda->side_dist.y);
	// printf("deltax %f  deltay %f\n\n", dda->delta_dist.x, dda->delta_dist.y);
}

void	ft_down(t_vars *vars, t_ray *ray)
{
	if (vars->map[(int)((vars->player.y ) - ray->dir.y * vars->player.movespeed)][(int)(vars->player.x)] != '1')
		(vars->player.y ) -= ray->dir.y * vars->player.movespeed;
    if (vars->map[(int)((vars->player.y ))][(int)(vars->player.x - ray->dir.x * vars->player.movespeed)] != '1')
		vars->player.x -= ray->dir.x * vars->player.movespeed;
	// printf("x = %f, y = %f, side_dist.x = %f, side_dist.y = %f\n", vars->player.x , vars->player.y, dda->side_dist.x, dda->side_dist.y);
	// printf("dir.x %f, dir.x  %f,  planex  %f, camerax %f\n", ray->dir.x, ray->dir.x, ray->plane.x, ray->camerax);
	// printf("dir.y %f, dir.y  %f,  planey  %f\n", ray->dir.y, ray->dir.y, ray->plane.y);
	// printf("deltax %f  deltay %f\n\n", dda->delta_dist.x, dda->delta_dist.y);

}

void	right_step(t_vars *vars, t_ray *ray)
{
	if(vars->map[(int)((vars->player.y ) + ray->plane.y * vars->player.movespeed)][(int)(vars->player.x)] != '1')
		(vars->player.y ) += ray->plane.y * vars->player.movespeed;
    if(vars->map[(int)((vars->player.y ))][(int)(vars->player.x + ray->plane.x * vars->player.movespeed)] != '1')
		vars->player.x += ray->plane.x * vars->player.movespeed;
}

void	left_step(t_vars *vars, t_ray *ray)
{
	if (vars->map[(int)((vars->player.y ) - ray->plane.y * vars->player.movespeed)][(int)(vars->player.x)] != '1')
		(vars->player.y ) -= ray->plane.y * vars->player.movespeed;
    if (vars->map[(int)((vars->player.y ))][(int)(vars->player.x - ray->plane.x * vars->player.movespeed)] != '1')
		vars->player.x -= ray->plane.x * vars->player.movespeed;
}
