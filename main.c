/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/10/16 16:56:43 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	draw_ceiling(t_vars *vars, int x, int y)
{
	int	y1;

	y1 = 0;
	while (y1 < y)
	{
		mlx_put_pixel(vars->game, x, y1, 0xFF0000);
		y1++;
	}
}

static void	draw_floor(t_vars *vars, int x, int y)
{
	while (y < HEIGHT)
	{
		mlx_put_pixel(vars->game, x, y, 0x000FFF);
		y++;
	}
}

static void	reset_window(t_vars *vars)
{
	int	x;
	int y = 0;

	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(vars->game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	verline(t_vars *vars, int x, int y1, int y2, uint32_t color)
{
	(void)color;
	if (y2 < 0)
		y2 = 0;
	if (y1 > HEIGHT)
		y1 = HEIGHT;
	int	tmp;
	if (y1 > y2)
	{
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
	draw_ceiling(vars, x, y1);
	draw_floor(vars, x, y2);
    for (int y = y1; y <= y2; y++) {
        mlx_put_pixel(vars->game, x, y, 0xFFFFFF);
    }
}
/*
void	dda(t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (ray->mapy < 0.25	|| ray->mapx < 0.25 || ray->mapy > 7 - 0.25
			|| ray->mapx > 7 - 1.25)
				break ;
		if (vars->map[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
	}
}*/

void	ft_draw_walls(t_vars *vars, t_ray *ray)
{
	uint32_t	color;
	init(vars);
	reset_window(vars);
	for (int x = 0;x < WIDTH;x++)
	{
		ray->mapx = (int)(vars->player.x);
		ray->mapy = (int)(vars->player.y);
		ray->camerax = 2 * x / (double)(WIDTH - 1);
		ray->raydirx = ray->dirx + ray->plane_x * ray->camerax;
		ray->raydiry = ray->diry + ray->plane_y * ray->camerax;
		//ray->deltadistx = fabs(1 / ray->raydirx);
 		//ray->deltadisty = fabs(1 / ray->raydiry);
		ray->deltadistx = (ray->raydirx == 0) ? 1e30 : fabs(1 / ray->raydirx);
     	ray->deltadisty = (ray->raydiry == 0) ? 1e30 : fabs(1 / ray->raydiry);
		if (ray->raydirx < 0)
		{
			ray->stepx = -1;
			ray->sidedistx = (vars->player.x - ray->mapx) * ray->deltadistx;
		}
		else
		{
			ray->stepx = 1;
			ray->sidedistx = (ray->mapx + 1.0 - vars->player.x) * ray->deltadistx;
		}
		if (ray->raydiry < 0)
		{
			ray->stepy = -1;
			ray->sidedisty = (vars->player.y - ray->mapy) * ray->deltadisty;
		}
		else
		{
			ray->stepy = 1;
			ray->sidedisty = (ray->mapy + 1.0 - vars->player.y) * ray->deltadisty;
		}
		ray->hit = 0;
		while (ray->hit == 0)
		{
			if (ray->sidedistx < ray->sidedisty)
			{
				ray->sidedistx += ray->deltadistx;
				ray->mapx += ray->stepx;
				ray->side = 0;
			}
			else
			{
				ray->sidedisty += ray->deltadisty;
				ray->mapy += ray->stepy;
				ray->side = 1;
			}
			if (ray->mapy < 0.25	|| ray->mapx < 0.25 || ray->mapy > 7 - 0.25
				|| ray->mapx > 7 - 1.25)
					break ;
			if (vars->map[ray->mapy][ray->mapx] == '1')
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
		else
			ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
		ray->lineheight = (int)(HEIGHT / ray->perpwalldist);
		ray->drawstart = -(ray->lineheight) / 2 + HEIGHT / 2;
		if (ray->drawstart < 0)
			ray->drawstart = 0;
		ray->drawend = ray->lineheight / 2 + HEIGHT / 2;
		if (ray->drawend >= HEIGHT)
			ray->drawend = HEIGHT - 1;
		if (vars->map[ray->mapx][ray->mapy] == '1')
    		color = 0xFF0000;
		else
			color = 0xFFFFFFFF;
      	if (ray->side == 1)
			color = color / 2;
		//draw_ceiling(vars, i);
		//printf("x = %d, lin = %d, start  %d, end %d  perp = %f\n",x,ray->lineheight,ray->drawstart,ray->drawend, ray->perpwalldist);
		verline(vars, x, ray->drawstart, ray->drawend, color);
	}
	vars->player.movespeed = vars->mlx->delta_time * 5.0;
	vars->player.rotspeed = vars->mlx->delta_time * 4.0;
	//printf("fps = %f\n", 1.0 / vars->mlx->delta_time);
}

void ft_hook(void* param)
{
	t_vars *vars  = param;

	//ft_draw_pixels_grid(vars);
	//ft_draw_pixels_player(vars);	
	//draw_floor(vars);
	ft_draw_walls(vars, &vars->ray);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(vars->mlx);
		free(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		left_step(vars, &vars->ray);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		right_step(vars, &vars->ray);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		ft_up(vars, &vars->ray);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		ft_down(vars, &vars->ray);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotate_left(vars, &vars->ray);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotate_right(vars, &vars->ray);
	//vars->player.image->instances[0].x = (int)(vars->player.x * 50);
	//vars->player.image->instances[0].y = (int)(vars->player.y * 50);
	/*vars->minimap->instances[0].x = (int)(vars->player.x * 50);
	vars->minimap->instances[0].y = (int)(vars->player.y * 50);*/
}

int    start_loop(t_vars *vars)
{   
	vars->mlx = mlx_init(WIDTH, HEIGHT, "cub", true);
	//vars->minimap = mlx_new_image(vars->mlx, 400, 400);
	vars->game = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	//vars->player.image = mlx_new_image(vars->mlx, 6, 6);
	mlx_image_to_window(vars->mlx, vars->game, 0, 0);
	//mlx_image_to_window(vars->mlx, vars->minimap, 0, 0);
	//mlx_image_to_window(vars->mlx, vars->player.image, (int)vars->player.x * 50, (int)vars->player.y * 50);
	//ft_draw_pixels_grid(vars);
	//ft_draw_pixels_player(vars);
	vars->ray.plane_x = 0;
	vars->ray.plane_y = 0.66;
	ft_draw_walls(vars, &vars->ray);
	mlx_loop_hook(vars->mlx, ft_hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}

void    find_pos(t_vars *vars, char **map)
{
    int i;
    int j;

    i = 0;
    while (map && map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] != '0' && map[i][j] != '1')
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

int main(int32_t argc, const char* argv[])
{
	t_vars *vars;

	vars = malloc(sizeof(t_vars));
    (void)argc;(void)argv;
    init(vars);
    vars->map = ft_split("11111111111:10000000001:10000000001:10100W00001:10000000001:"
		"10000000001:10000000001:10000000001:10000000001:10000000001:11111111111",':');
	find_pos(vars, vars->map);
	init_orientation(vars);
	start_loop(vars);
	return (EXIT_SUCCESS);
}
