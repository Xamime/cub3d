/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 02:00:39 by max               #+#    #+#             */
/*   Updated: 2023/10/17 01:09:49 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void    rotate_left(t_vars *vars, t_ray *ray)
{
	/*vars->player.angle += 0.1;
	if (vars->player.angle > 6.28318530718)
		vars->player.angle -= 2 * PI;*/
	double oldDirX = ray->dirx;
    ray->dirx = ray->dirx * cos(vars->player.rotspeed) - ray->diry * sin(vars->player.rotspeed);
    ray->diry = oldDirX * sin(vars->player.rotspeed) + ray->diry * cos(vars->player.rotspeed);
    double oldPlaneX = ray->plane_x;
    ray->plane_x = ray->plane_x * cos(vars->player.rotspeed) - ray->plane_y * sin(vars->player.rotspeed);
    ray->plane_y = oldPlaneX * sin(vars->player.rotspeed) + ray->plane_y * cos(vars->player.rotspeed);
	// printf("dirx %f, dirx  %f,  planex  %f, camerax %f\n", ray->dirx, ray->dirx, ray->plane_x, ray->camerax);
	// printf("diry %f, diry  %f,  planey  %f\n", ray->diry, ray->diry, ray->plane_y);
	// printf("x = %f, y = %f, sidedistx = %f, sidedisty = %f\n", vars->player.x , vars->player.y, ray->sidedistx, ray->sidedisty);
	// printf("deltax %f  deltay %f\n\n", ray->deltadistx, ray->deltadisty);
}

void    rotate_right(t_vars *vars, t_ray *ray)
{
	/*vars->player.angle -= 0.1;
	if (vars->player.angle < 0)
		vars->player.angle += 2 * PI;*/
		double oldDirX = ray->dirx;
      ray->dirx = ray->dirx * cos(-(vars->player.rotspeed)) - ray->diry * sin(-(vars->player.rotspeed));
      ray->diry = oldDirX * sin(-(vars->player.rotspeed)) + ray->diry * cos(-(vars->player.rotspeed));
      double oldPlaneX = ray->plane_x;
      ray->plane_x = ray->plane_x * cos(-(vars->player.rotspeed)) - ray->plane_y * sin(-(vars->player.rotspeed));
      ray->plane_y = oldPlaneX * sin(-(vars->player.rotspeed)) + ray->plane_y * cos(-(vars->player.rotspeed));
	// printf("dirx %f, dirx  %f,  planex  %f, camerax %f\n", ray->dirx, ray->dirx, ray->plane_x, ray->camerax);
	// printf("diry %f, diry  %f,  planey  %f\n", ray->diry, ray->diry, ray->plane_y);
	// printf("x = %f, y = %f, sidedistx = %f, sidedisty = %f\n", vars->player.x , vars->player.y, ray->sidedistx, ray->sidedisty);
	// printf("deltax %f  deltay %f\n\n", ray->deltadistx, ray->deltadisty);
}

void	ft_up(t_vars *vars, t_ray *ray)
{
	/*double tmpx = vars->player.x;
	double tmpy = vars->player.y;

	tmpx = vars->player.x + (SPEED * cos(vars->player.angle));
	tmpy = vars->player.y + (SPEED * sin(vars->player.angle));
	if (vars->map[(int)(tmpy )][(int)(tmpx )] != '1')
		vars->player.x = tmpx;

	if (vars->map[(int)(tmpy )][(int)(tmpx )] != '1')
		vars->player.y = tmpy;*/\

	//If vars->map[new_y][current_x] != '1' then player_y = new_y
	//If vars->map[current_y][new_x] != '1' then player_x = new_x
	if(vars->map[(int)((vars->player.y ) + ray->diry * vars->player.movespeed)][(int)(vars->player.x)] != '1')
		(vars->player.y ) += ray->diry * vars->player.movespeed;
    if(vars->map[(int)((vars->player.y ))][(int)(vars->player.x + ray->dirx * vars->player.movespeed)] != '1')
		vars->player.x += ray->dirx * vars->player.movespeed;
	// printf("dirx %f, dirx  %f,  planex  %f, camerax %f\n", ray->dirx, ray->dirx, ray->plane_x, ray->camerax);
	// printf("diry %f, diry  %f,  planey  %f\n", ray->diry, ray->diry, ray->plane_y);
	// printf("x = %f, y = %f, sidedistx = %f, sidedisty = %f\n", vars->player.x , vars->player.y, ray->sidedistx, ray->sidedisty);
	// printf("deltax %f  deltay %f\n\n", ray->deltadistx, ray->deltadisty);
}

void	ft_down(t_vars *vars, t_ray *ray)
{
	/*double tmpx = vars->player.x;
	double tmpy = vars->player.y;

	tmpx = vars->player.x - (SPEED * cos(vars->player.angle));
	tmpy = vars->player.y - (SPEED * sin(vars->player.angle));
	if (vars->map[(int)(tmpy )][(int)(tmpx )] != '1')
		vars->player.x = tmpx;

	if (vars->map[(int)(tmpy )][(int)(tmpx )] != '1')
		vars->player.y = tmpy;*/
	// printf("x = %f, y = %f, sidedistx = %f, sidedisty = %f\n", vars->player.x , vars->player.y, ray->sidedistx, ray->sidedisty);
	if (vars->map[(int)((vars->player.y ) - ray->diry * vars->player.movespeed)][(int)(vars->player.x)] != '1')
		(vars->player.y ) -= ray->diry * vars->player.movespeed;
    if (vars->map[(int)((vars->player.y ))][(int)(vars->player.x - ray->dirx * vars->player.movespeed)] != '1')
		vars->player.x -= ray->dirx * vars->player.movespeed;
	// printf("x = %f, y = %f, sidedistx = %f, sidedisty = %f\n", vars->player.x , vars->player.y, ray->sidedistx, ray->sidedisty);
	// printf("dirx %f, dirx  %f,  planex  %f, camerax %f\n", ray->dirx, ray->dirx, ray->plane_x, ray->camerax);
	// printf("diry %f, diry  %f,  planey  %f\n", ray->diry, ray->diry, ray->plane_y);
	// printf("deltax %f  deltay %f\n\n", ray->deltadistx, ray->deltadisty);

}

void	left_step(t_vars *vars, t_ray *ray)
{

}

void	right_step(t_vars *vars, t_ray *ray)
{

}
