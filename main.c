/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/09/28 16:04:00 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void    rotate_right(t_vars *vars)
{
	vars->player.angle += 0.1;
	if (vars->player.angle > 6.28318530718)
		vars->player.angle -= 2 * PI;
	/*vars->player.ray.deltadistX = cos(vars->player.angle) * SPEED;
	vars->player.ray.deltadistY = sin(vars->player.angle) * SPEED;*/
	printf("x = %f y = %f angle = %f\n", vars->player.x, vars->player.y,vars->player.angle );
}

void    rotate_left(t_vars *vars)
{
	vars->player.angle -= 0.1;
	if (vars->player.angle < 0)
		vars->player.angle += 2 * PI;
	/*vars->player.ray.deltadistX = cos(vars->player.angle) * SPEED;
	vars->player.ray.deltadistY = sin(vars->player.angle) * SPEED;*/
	printf("x = %d y = %f angle = %f\n", vars->player.image->instances[0].x , vars->player.y,vars->player.angle );
}

void	ft_up(t_vars *vars)
{
	double tmpx = vars->player.x;
	double tmpy = vars->player.y;

	tmpx = vars->player.x + (SPEED * cos(vars->player.angle));
	tmpy = vars->player.y + (SPEED * sin(vars->player.angle));
	if (vars->map[(int)(tmpy / 50)][(int)(tmpx / 50)] != '1')
		vars->player.x = tmpx;
	
	if (vars->map[(int)(tmpy / 50)][(int)(tmpx / 50)] != '1')
		vars->player.y = tmpy;
	printf("x = %f y = %f angle = %f\n", vars->player.x, vars->player.y,vars->player.angle );

	//printf("x = %f, y = %f\n", vars->player.x,vars->player.y);
	/*if (check_wall(vars, vars->player.x + 3 + vars->player.ray.deltadistX, vars->player.y + 3 + vars->player.ray.deltadistY))
	{
		vars->player.y += vars->player.ray.deltadistY;
		vars->player.x += vars->player.ray.deltadistX;
		vars->player.image->instances[0].x = vars->player.x + 0.5;
		vars->player.image->instances[0].y = vars->player.y + 0.5;
	}*/
	//printf("x = %f y = %f angle = %f\n", vars->player.x, vars->player.y,vars->player.angle );
}

void	ft_down(t_vars *vars)
{
	/*
	if (check_wall(vars, vars->player.x + 3 - vars->player.ray.deltadistX, vars->player.y + 3 - vars->player.ray.deltadistY))
	{
		vars->player.x -= vars->player.ray.deltadistX;
		vars->player.y -= vars->player.ray.deltadistY;
		vars->player.image->instances[0].x = vars->player.x + 0.5;
		vars->player.image->instances[0].y = vars->player.y + 0.5;
	}*/
	double tmpx = vars->player.x;
	double tmpy = vars->player.y;

	tmpx = vars->player.x - (SPEED * cos(vars->player.angle));
	tmpy = vars->player.y - (SPEED * sin(vars->player.angle));
	if (vars->map[(int)(tmpy / 50)][(int)(tmpx / 50)] != '1')
		vars->player.x = tmpx;
	
	if (vars->map[(int)(tmpy / 50)][(int)(tmpx / 50)] != '1')
		vars->player.y = tmpy;
	printf("x = %f y = %f angle = %f\n", vars->player.x, vars->player.y,vars->player.angle );

}

void	left_step(t_vars *vars)
{
	
}

void	right_step(t_vars *vars)
{

}

static void	draw_ceiling(t_vars *vars)
{
	int	color;
	int	y;

	y = 0;
	// color = rgba_to_int(colors->i_ceiling[0], colors->i_ceiling[1], \
	// 	colors->i_ceiling[2], 255);
	while (y < vars->ray.drawstart)
	{
		mlx_put_pixel(vars->minimap, vars->player.x, y,	0xFFFFFF);
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

static void	draw_floor(t_vars *vars)
{
	int	color;
	int y = 0;

	// color = rgba_to_int(colors->i_floor[0], colors->i_floor[1], \
	// 	colors->i_floor[2], 255);
	while (y < HEIGHT)
	{
		mlx_put_pixel(vars->minimap, vars->player.x, y, 0x000000);
		y++;
	}
}

void	ft_draw_walls(t_vars *vars)
{
	int	mapx;
	int	mapy;
	int	stepx;
	int	stepy;
	
	mapx = (int)vars->player.x / 50;
	mapy = (int)vars->player.y / 50;
	for (int i = 0;i < HEIGHT;i++)
	{
		vars->ray.camerax = 2 * i / (double)(WIDTH - 1);
		vars->ray.raydirx = vars->ray.dirx + vars->ray.plane_x * vars->ray.camerax;
		vars->ray.raydiry = vars->ray.diry + vars->ray.plane_y * vars->ray.camerax;
		vars->ray.deltadistx = fabs(1 / vars->ray.raydirx);
 		vars->ray.deltadisty = fabs(1 / vars->ray.raydiry);
		if (vars->ray.raydirx < 0)
		{
			stepx = -1;
			vars->ray.sidedistx = (vars->player.x - mapx) * vars->ray.deltadistx;
		}
		else
		{
			stepx = 1;
			vars->ray.sidedistx = (mapx + 1.0 - vars->player.x) * vars->ray.deltadistx;
		}
		if (vars->ray.raydiry < 0)
		{
			stepy = -1;
			vars->ray.sidedisty = (vars->player.y - mapy) * vars->ray.deltadisty;
		}
		else
		{
			stepy = 1;
			vars->ray.sidedisty = (mapy + 1.0 - vars->player.y) * vars->ray.deltadisty;
		}
		while (vars->ray.hit == 0)
		{
			if (vars->ray.sidedistx < vars->ray.sidedisty)
			{
				vars->ray.sidedistx += vars->ray.deltadistx;
				mapx += stepx;
				vars->ray.side = 0;
			}
			else
			{
				vars->ray.sidedisty += vars->ray.deltadisty;
				mapy += stepy;
				vars->ray.side = 1;
			}
			//printf("mapy = %d mapx = %d\n", mapy,mapx);
			if (vars->map[mapy][mapx] == '1')
				vars->ray.hit = 1;
		}
		if (vars->ray.side == 0)
			vars->ray.perpwalldist = (vars->ray.sidedistx - vars->ray.deltadistx);
		else
			vars->ray.perpwalldist = (vars->ray.sidedisty - vars->ray.deltadisty);
		vars->ray.lineheight = (int)(HEIGHT / vars->ray.perpwalldist);
		vars->ray.drawstart = -vars->ray.lineheight / 2 + HEIGHT / 2;
		if (vars->ray.drawstart < 0)
			vars->ray.drawstart = 0;
		vars->ray.drawend = vars->ray.lineheight / 2 + HEIGHT / 2;
		if (vars->ray.drawend >= HEIGHT)
			vars->ray.drawend = HEIGHT - 1;
	}
}

void ft_hook(void* param)
{
	t_vars *vars  = param;

	//ft_draw_pixels_grid(vars);
	//ft_draw_pixels_player(vars);
	draw_ceiling(vars);
	draw_floor(vars);
	ft_draw_walls(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		left_step(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		right_step(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		ft_up(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		ft_down(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotate_left(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotate_right(vars);
}

int    start_loop(t_vars *vars)
{   
	vars->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	vars->minimap = mlx_new_image(vars->mlx, HEIGHT, HEIGHT);
	//vars->player.image = mlx_new_image(vars->mlx, 6, 6);
	mlx_image_to_window(vars->mlx, vars->minimap, 0, 0);
	//mlx_image_to_window(vars->mlx, vars->player.image, vars->player.x, vars->player.y);
	
	/*ft_draw_pixels_grid(vars);
	ft_draw_pixels_player(vars);*/
	printf("player x : %f, player y : %f, player angle : %f\n", vars->player.x, vars->player.y,vars->player.angle);

	mlx_loop_hook(vars->mlx, ft_hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}

void  init(t_vars *vars)
{
	vars->ray.lineheight = 0;
	vars->ray.drawend = 0;
	vars->ray.drawstart = 0;
	vars->ray.y = 0;
	vars->ray.x = 0;
	vars->ray.camerax = 0;
	vars->player.angle = 0;
	vars->ray.plane_x = 0;
	vars->ray.plane_y = 0.66;
	vars->ray.sidedisty = 0;
	vars->ray.sidedistx = 0;
	vars->ray.deltadistx = 0;
	vars->ray.deltadisty = 0;
	vars->ray.hit = 0;
	vars->ray.side = 0;
	vars->ray.orientation = 0;
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
                vars->player.x = j * 50;
                vars->player.y = i * 50;
	            vars->player.orientation = map[i][j];
            }
            j++;
        }
        i++;
    }
}

void	init_orientation(t_vars *vars)
{
	if (vars->player.orientation == 'N')
	{
		vars->ray.dirx = 0;
		vars->ray.diry = -1;
		vars->player.angle = PI / 2;
	}
	else if (vars->player.orientation == 'E')
	{
		vars->ray.dirx = 1;
		vars->ray.diry = 0;
		vars->player.angle = PI * 2;
	}
	else if (vars->player.orientation == 'W')
	{
		vars->ray.dirx = -1;
		vars->ray.diry = 0;
		vars->player.angle = PI;
	}
	else if (vars->player.orientation == 'S')
	{
		vars->ray.dirx = 0;
		vars->ray.diry = 1;
		vars->player.angle = PI * 3 / 2;
	}
}

int32_t main(int32_t argc, const char* argv[])
{
	t_vars *vars;

	vars = malloc(sizeof(t_vars));
    (void)argc;(void)argv;
    init(vars);
    vars->map = ft_split("11111111:10100011:10110001:10000W01:10100011:10100101:10100011:11111111",':');
	find_pos(vars, vars->map);
	init_orientation(vars);
	start_loop(vars);
	return (EXIT_SUCCESS);
}
