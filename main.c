/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/09/24 18:07:31 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

#define WIDTH 1024
#define HEIGHT 512
#define ROTATE 2.50
#define PI 3.14159265359

void    rotate_right(t_vars *vars)
{
	vars->player.angle += 0.1;
	if (vars->player.angle > (2 * PI))
		vars->player.angle -= 2 * PI;
	vars->player.ray.deltadistX = cos(vars->player.angle) *4;
	vars->player.ray.deltadistY = sin(vars->player.angle) *4;
}

void    rotate_left(t_vars *vars)
{
	vars->player.angle -= 0.1;
	if (vars->player.angle < 0)
		vars->player.angle += 2 * PI;
	vars->player.ray.deltadistX = cos(vars->player.angle) *4;
	vars->player.ray.deltadistY = sin(vars->player.angle) *4;
}

void	ft_up(t_vars *vars)
{
	vars->player.x += vars->player.ray.deltadistX;
	vars->player.y += vars->player.ray.deltadistY;
	vars->player.image->instances[0].x = vars->player.x + 0.5;
	vars->player.image->instances[0].y = vars->player.y + 0.5;
}

void	ft_down(t_vars *vars)
{
	// vars->player.image->instances[0].x -= vars->player.ray.deltadistX;
	// vars->player.image->instances[0].y -= vars->player.ray.deltadistY;
	vars->player.x -= vars->player.ray.deltadistX;
	vars->player.y -= vars->player.ray.deltadistY;
	vars->player.image->instances[0].x = vars->player.x + 0.5;
	vars->player.image->instances[0].y = vars->player.y + 0.5;

}

void ft_hook(void* param)
{
	t_vars *vars  = param;

	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		ft_up(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		ft_down(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotate_left(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotate_right(vars);
	//vars->player.x = (double)vars->player.image->instances[0].x / 500;
	//vars->player.y = (double)vars->player.image->instances[0].y / 500;
	printf("x = %f y = %f angle = %f\n", vars->player.x, vars->player.y,vars->player.angle );
}

int    initialization(t_vars *vars)
{
	int	i = 0;
	while (vars->map[i])
		i++;    
	vars->mlx = mlx_init(WIDTH, WIDTH, "cub3d", true);
	vars->minimap = mlx_new_image(vars->mlx, 500, 500);
	vars->player.image = mlx_new_image(vars->mlx, 10, 10);
	mlx_image_to_window(vars->mlx, vars->minimap, 0, 0);
	mlx_image_to_window(vars->mlx, vars->player.image, vars->player.x, vars->player.y);

	mlx_loop_hook(vars->mlx, ft_draw_pixels_grid, vars);
	mlx_loop_hook(vars->mlx, ft_draw_pixels_player, vars);
	mlx_loop_hook(vars->mlx, ft_hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}

// void    rotate_right(t_vars *vars)
// {
//     double    old_dir_y;
//     double    old_plane_y;
//     double    rotation;

//     rotation = ROTATE * (PI / 180.0);
//     old_dir_y = vars->player.ray.y;
//     rotation *= vars->orientation;
//     vars->player.ray.y = vars->player.ray.y * cosf(-rotation)
//         - vars->player.ray.x * sinf(-rotation);
//     vars->player.ray.x = old_dir_y * sinf(-rotation)
//         + vars->player.ray.x * cosf(-rotation);
//     old_plane_y = vars->player.ray.plane_y;
//     vars->player.ray.plane_y = vars->player.ray.plane_y * cosf(-rotation)
//         - vars->player.ray.plane_x * sinf(-rotation);
//     vars->player.ray.plane_x = old_plane_y * sinf(-rotation)
//         + vars->player.ray.plane_x * cosf(-rotation);
// }


void  init(t_vars *vars)
{
	vars->player.ray.y = 0;
	vars->player.ray.angle = 0;
	vars->player.ray.x = 0;
	vars->player.angle = 0;
	vars->player.ray.plane_x = 0;
	vars->player.ray.plane_y = 0;
	vars->player.ray.raydirX = 0;
	vars->player.ray.raydirY = 0;
	vars->player.ray.sidedistY = 0;
	vars->player.ray.sidedistX = 0;
	vars->player.ray.deltadistX = 0;
	vars->player.ray.deltadistY = sin(vars->player.angle) * 4;
	vars->player.ray.hit = 0;
	vars->player.ray.side = 0;
	vars->player.ray.orientation = 0;
	printf("init %f\n",vars->player.angle);
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
		vars->player.ray.x = 0;
		vars->player.ray.y = -1;
	}
	else if (vars->player.orientation == 'E')
	{
		vars->player.ray.x = 1;
		vars->player.ray.y = 0;
	}
	else if (vars->player.orientation == 'W')
	{
		vars->player.ray.x = -1;
		vars->player.ray.y = 0;
	}
	else if (vars->player.orientation == 'S')
	{
		vars->player.ray.x = 0;
		vars->player.ray.y = 1;
	}
}

int32_t main(int32_t argc, const char* argv[])
{
	t_vars *vars;

	vars = malloc(sizeof(t_vars));
    (void)argc;(void)argv;
    init(vars);
	printf("main %f\n",vars->player.angle);
    vars->map = ft_split("11111111:10100011:10110001:10000W01:10100011:10100101:10100011:11111111",':');
	find_pos(vars, vars->map);
	init_orientation(vars);
	initialization(vars);
}
