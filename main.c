/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/10/17 08:09:17 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	draw_ceiling(t_vars *vars, int x)
{
	int	color;
	int	y;

	y = 0;
	// color = rgba_to_int(colors->i_ceiling[0], colors->i_ceiling[1], \
	// 	colors->i_ceiling[2], 255);
	while (y < vars->ray.drawstart)
	{
		mlx_put_pixel(vars->minimap, x, y,	0xFFFFFF);
		y++;
	}
}

// static void	draw_textures(t_vars *vars)
// {
// 	float		step;
// 	float		tex_pos;

// 	step = 1.0 * data->images.n_wall->height / data->images.line_height;
// 	tex_pos = (data->images.draw_start - (1080 / 2) \
// 		+ data->images.line_height / 2) * step;
// 	ray->y = data->images.draw_start;
// 	while (ray->y < data->images.draw_end)
// 	{
// 		ray->tex_y = (int)tex_pos & (data->images.n_wall->height - 1);
// 		tex_pos += step;
// 		if (ray->hit_side == 1 && ray->step_y < 0)
// 			mlx_put_pixel(vars->minimap, data->images.x, ray->y, \
// 			get_color(data->images.s_wall, ray->tex_y, ray->tex_x));
// 		else if (ray->hit_side == 1 && ray->step_y > 0)
// 			mlx_put_pixel(vars->minimap, data->images.x, ray->y, \
// 			get_color(data->images.n_wall, ray->tex_y, ray->tex_x));
// 		else if (ray->hit_side == 0 && ray->step_x < 0)
// 			mlx_put_pixel(vars->minimap, data->images.x, ray->y, \
// 			get_color(data->images.e_wall, ray->tex_y, ray->tex_x));
// 		else if (ray->hit_side == 0 && ray->step_x > 0)
// 			mlx_put_pixel(vars->minimap, data->images.x, ray->y, \
// 			get_color(data->images.w_wall, ray->tex_y, ray->tex_x));
// 		ray->y++;
// 	}
// }

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
    for (int y = y1; y <= y2; y++) {
        mlx_put_pixel(vars->game, x, y, color);
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
		//if (ray->mapy < 0.25	|| ray->mapx < 0.25 || ray->mapy > 7 - 0.25
		//	|| ray->mapx > 7 - 1.25)
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
	for (int x = 0; x < WIDTH; x++)
	{
		ray->mapx = (int)(vars->player.x);
		ray->mapy = (int)(vars->player.y);
		ray->camerax = 2 * x / (double)(WIDTH - 1);
		double	dir_x = ray->dirx;
		double	dir_y = ray->diry;
		double	oldDirX = dir_x;
		double	angle = 44.7;
		dir_x = dir_x * cos(angle) - dir_y * sin(angle);
		dir_y = oldDirX * sin(angle) + dir_y * cos(angle);
		ray->raydirx = dir_x + ray->plane_x * ray->camerax;
		ray->raydiry = dir_y + ray->plane_y * ray->camerax;
		// ray->raydirx = ray->dirx + ray->plane_x * ray->camerax;
		// ray->raydiry = ray->diry + ray->plane_y * ray->camerax;
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
			// if (ray->mapy < 0.25	|| ray->mapx < 0.25 || ray->mapy > 7 - 0.25
			// 	|| ray->mapx > 7 - 1.25)
			// 		break ;
			if (vars->map[ray->mapy][ray->mapx] == '1')
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
		else
			ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
		ray->lineheight = (int)(HEIGHT / ray->perpwalldist);
		// ray->drawstart = -(ray->lineheight) / 2 + HEIGHT / 2;
		ray->drawstart = HEIGHT / 2 - ray->lineheight / 2;
		if (ray->drawstart < 0)
			ray->drawstart = 0;
		ray->drawend = HEIGHT / 2 + ray->lineheight / 2;
		if (ray->drawend >= HEIGHT)
			ray->drawend = HEIGHT - 1;
		if (vars->map[ray->mapx][ray->mapy] == '1')
    		color = create_argb(0, 255, 255, 255);
		else
			color = create_argb(0, 0, 0, 255);
      	if (ray->side == 1)
			color = create_argb(255, 0, 0, 255);
		if (!ray->hit)
			color = create_argb(255, 0, 255, 255);
		//draw_ceiling(vars, i);
		// printf("x = %d, lin = %d, start  %d, end %d  perp = %f\n",x,ray->lineheight,ray->drawstart,ray->drawend, ray->perpwalldist);
		verline(vars, x, ray->drawstart, ray->drawend, color);
	}
	vars->player.movespeed = vars->mlx->delta_time * 5.0;
	vars->player.rotspeed = vars->mlx->delta_time * 4.0;
	//printf("fps = %f\n", 1.0 / vars->mlx->delta_time);
	// ft_display_rays(vars, ray);
}

void ft_hook(void* param)
{
	t_vars *vars  = param;

	//ft_draw_pixels_grid(vars);
	//ft_draw_pixels_player(vars);
	//draw_floor(vars);
	// ft_draw_walls(vars, &vars->ray);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		left_step(vars, &vars->ray);
		ft_draw_walls(vars, &vars->ray);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		right_step(vars, &vars->ray);
		ft_draw_walls(vars, &vars->ray);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		ft_up(vars, &vars->ray);
		ft_draw_walls(vars, &vars->ray);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		ft_down(vars, &vars->ray);
		ft_draw_walls(vars, &vars->ray);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		rotate_left(vars, &vars->ray);
		ft_draw_walls(vars, &vars->ray);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		rotate_right(vars, &vars->ray);
		ft_draw_walls(vars, &vars->ray);
	}
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_1))
	// {
	// 	vars->ray.plane_x += 0.01f;
	// 	vars->ray.plane_y += 0.01f;
	// 	ft_draw_walls(vars, &vars->ray);
	// }
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_2) && vars->ray.plane_x > 0.1f)
	// {
	// 	vars->ray.plane_x -= 0.01f;
	// 	vars->ray.plane_y -= 0.01f;
	// 	ft_draw_walls(vars, &vars->ray);
	// }
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
	t_vars	vars;

	(void)argc;(void)argv;
	init(&vars);
	/*
	11111111
	10000001
	10000001
	101W0001
	10000001
	10000001
	10000001
	11111111*/
	vars.map = ft_split("11111111:10000001:10000001:101S0001:10000001:10000001:10000001:11111111",':');
	find_pos(&vars, vars.map);
	init_orientation(&vars);
	start_loop(&vars);
	for (int i = 0; vars.map[i]; i++)
		free(vars.map[i]);
	free(vars.map);
	return (EXIT_SUCCESS);
}
