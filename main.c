/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/09/26 19:07:54 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void    rotate_right(t_vars *vars)
{
	// vars->player.angle += 0.1;
	// if (vars->player.angle > 6.28318530718)
	// 	vars->player.angle -= 2 * PI;
	// vars->player.ray.deltadistX = cos(vars->player.angle) * SPEED;
	// vars->player.ray.deltadistY = sin(vars->player.angle) * SPEED;
	printf("player x : %f, player y : %f, player angle : %f\n", vars->player.x, vars->player.y,vars->player.angle);
}

void    rotate_left(t_vars *vars)
{
	// vars->player.angle -= 0.1;
	// if (vars->player.angle < 0)
	// 	vars->player.angle += 2 * PI;
	// vars->player.ray.deltadistX = cos(vars->player.angle) * SPEED;
	// vars->player.ray.deltadistY = sin(vars->player.angle) * SPEED;
	printf("player x : %f, player y : %f, player angle : %f\n", vars->player.x, vars->player.y,vars->player.angle);
}

void	ft_up(t_vars *vars)
{
	if (vars->map[(int)(vars->player.x + vars->player.ray.dirX * SPEED) / 50][(int)vars->player.y / 50] == '0')
	{
		vars->player.x += vars->player.ray.dirX * SPEED;
		printf("test= %f\n",vars->player.ray.dirX * SPEED);
	}
	if (vars->map[(int)vars->player.x][(int)(vars->player.y + vars->player.ray.dirY * SPEED)] == '0')
	{
		printf("yooo\n\n\n\n");

		vars->player.y += vars->player.ray.dirY * SPEED;
	}
	//printf("yoyoo %d et %d\n",(int)(vars->player.x + vars->player.ray.dirX * SPEED), (int)(vars->player.y + vars->player.ray.dirY * SPEED));
	// vars->player.x += vars->player.ray.deltadistX;
	// vars->player.y += vars->player.ray.deltadistY;
	vars->player.image->instances[0].x = vars->player.x + 0.5;
	vars->player.image->instances[0].y = vars->player.y + 0.5;
	printf("player x : %f, player y : %f, player angle : %f\n", vars->player.x, vars->player.y,vars->player.angle);
}

void	ft_down(t_vars *vars)
{
	// vars->player.x -= vars->player.ray.deltadistX;
	// vars->player.y -= vars->player.ray.deltadistY;
	// vars->player.image->instances[0].x = vars->player.x + 0.5;
	// vars->player.image->instances[0].y = vars->player.y + 0.5;
	printf("player x : %f, player y : %f, player angle : %f\n", vars->player.x, vars->player.y,vars->player.angle);
}

void	left_step(t_vars *vars)
{
	// vars->player.x += vars->player.ray.deltadistX;
	// vars->player.y += vars->player.ray.deltadistY;
	// vars->player.image->instances[0].x = vars->player.x + 0.5;
	// vars->player.image->instances[0].y = vars->player.y + 0.5;
	// printf("x = %f y = %f angle = %f\n", vars->player.x, vars->player.y,vars->player.angle );
	printf("player x : %f, player y : %f, player angle : %f\n", vars->player.x, vars->player.y,vars->player.angle);
}

void	right_step(t_vars *vars)
{
	printf("player x : %f, player y : %f, player angle : %f\n", vars->player.x, vars->player.y,vars->player.angle);
}

void ft_hook(void* param)
{
	t_vars *vars  = param;

	
		// vars->player.x = (double)(vars->player.image->instances[0].x / 500.00f);
		// vars->player.y = (double)(vars->player.image->instances[0].y / 500.00f);
	
	int mapX = (int)vars->player.x;
	int mapY = (int)vars->player.y;
	int	stepx = 0;
	int	stepy = 0;
	for (int i = 0; i < HEIGHT;i++)
	{
		vars->player.ray.camerax = 2 * i / (double)HEIGHT - 1.00f;
		vars->player.ray.raydirx = vars->player.ray.dirX + (vars->player.ray.plane_x * vars->player.ray.camerax);
		vars->player.ray.raydiry = vars->player.ray.dirY + (vars->player.ray.plane_y * vars->player.ray.camerax);
		vars->player.ray.deltadistX = (vars->player.ray.raydirx == 0) ? 1e30 : fabs(1 / vars->player.ray.raydirx);
		vars->player.ray.deltadistY = (vars->player.ray.raydiry == 0) ? 1e30 : fabs(1 / vars->player.ray.raydiry);
		//printf("delta= %f\n",vars->player.ray.deltadistX);
		if (vars->player.ray.raydirx < 0)
		{
			stepx = -1;
			vars->player.ray.sidedistX = (vars->player.x - mapX) * vars->player.ray.deltadistX;
		}
		else
		{
			stepx = 1;
			vars->player.ray.sidedistX = (mapX + 1.0 - vars->player.x) * vars->player.ray.deltadistX;
		}
		if (vars->player.ray.raydiry < 0)
		{
			stepy = -1;
			vars->player.ray.sidedistY = (vars->player.y - mapY) * vars->player.ray.deltadistY;
		}
		else
		{
			stepy = 1;
			vars->player.ray.sidedistY = (mapY + 1.0 - vars->player.y) * vars->player.ray.deltadistY;
		}
		while (vars->player.ray.hit == 0)
		{
			if (vars->player.ray.sidedistX < vars->player.ray.sidedistY)
			{
				vars->player.ray.sidedistX += vars->player.ray.deltadistX;
				mapX += stepx;
				vars->player.ray.side = 0;
			}
			else
			{
				vars->player.ray.sidedistY += vars->player.ray.deltadistY;
				mapY += stepy;
				vars->player.ray.side = 1;
			}
			printf("mapx = %d mapy = %d\n",mapX, mapY);
			if (mapY > 0)
				mlx_put_pixel(vars->minimap, mapX, mapY, 0xFF0000FF);
			if (vars->map[mapX][mapY] == 1)
				vars->player.ray.hit = 1;
		}
	}
	if (vars->player.ray.side == 0)
		vars->player.ray.perpwalldist = (vars->player.ray.sidedistX - vars->player.ray.deltadistX);
	else
		vars->player.ray.perpwalldist = (vars->player.ray.sidedistY - vars->player.ray.deltadistY);

    //Calculate height of line to draw on screen
	int	lineheight = HEIGHT / vars->player.ray.perpwalldist;

	 //calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineheight / 2 + HEIGHT / 2;
    if (drawStart < 0)
		drawStart = 0;
    int drawEnd = lineheight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT)
		drawEnd = HEIGHT - 1;
	double oldtime = vars->mlx->delta_time;
	

	ft_draw_pixels_grid(vars);
	ft_draw_pixels_player(vars);
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
	int	i = 0;
	while (vars->map[i])
		i++;    
	vars->mlx = mlx_init(HEIGHT, HEIGHT, "cub3d", true);
	vars->minimap = mlx_new_image(vars->mlx, HEIGHT, HEIGHT);
	vars->player.image = mlx_new_image(vars->mlx, 10, 10);
	mlx_image_to_window(vars->mlx, vars->minimap, 0, 0);
	mlx_image_to_window(vars->mlx, vars->player.image, vars->player.x, vars->player.y);

	ft_draw_pixels_grid(vars);
	ft_draw_pixels_player(vars);
	printf("player x : %f, player y : %f, player angle : %f\n", vars->player.x, vars->player.y,vars->player.angle);

	mlx_loop_hook(vars->mlx, ft_hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}

void  init(t_vars *vars)
{
	vars->player.ray.y = 0;
	vars->player.ray.x = 0;
	vars->player.angle = 0;
	vars->player.ray.plane_x = 0;
	vars->player.ray.plane_y = 0.66;
	vars->player.ray.dirX = -1;
	vars->player.ray.dirY = 0;
	vars->player.ray.sidedistY = 0;
	vars->player.ray.sidedistX = 0;
	vars->player.ray.deltadistX = 0;
	vars->player.ray.deltadistY = 0;
	vars->player.ray.hit = 0;
	vars->player.ray.side = 0;
	vars->player.ray.orientation = 0;
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
		vars->player.ray.dirX = 0;
		vars->player.ray.dirY = -1;
		vars->player.angle = 1.57 + PI;
	}
	else if (vars->player.orientation == 'E')
	{
		vars->player.ray.dirX = 1;
		vars->player.ray.dirY = 0;
		vars->player.angle = 0;
	}
	else if (vars->player.orientation == 'W')
	{
		vars->player.ray.dirX = -1;
		vars->player.ray.dirY = 0;
		vars->player.angle = PI;
	}
	else if (vars->player.orientation == 'S')
	{
		vars->player.ray.dirX = 0;
		vars->player.ray.dirY = 1;
		vars->player.angle = 1.57;
	}
}

int32_t main(int32_t argc, const char* argv[])
{
	t_vars *vars;

	vars = malloc(sizeof(t_vars));
    (void)argc;(void)argv;
    init(vars);
    vars->map = ft_split("11111111:10100011:10110001:10000N01:10100011:10100101:10100011:11111111",':');
	find_pos(vars, vars->map);
	init_orientation(vars);
	start_loop(vars);
	return (EXIT_SUCCESS);
}
