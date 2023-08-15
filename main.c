/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/15 19:42:41 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

#define WIDTH 1024
#define HEIGHT 512
#define ROTATE 2.50
#define PI 3,14159265358979

void ft_hook(void* param)
{
	t_vars *vars  = param;

	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		vars->player.image->instances[0].y -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		vars->player.image->instances[0].y += 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		vars->player.image->instances[0].x -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		vars->player.image->instances[0].x += 5;
		//rotate_right(vars);
	}
	vars->player.x = (double)vars->player.image->instances[0].x / 500;
	vars->player.y = (double)vars->player.image->instances[0].y / 500;
	//printf("%f %f\n", vars->player.x, vars->player.y );
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
	mlx_image_to_window(vars->mlx, vars->player.image, vars->player.x * 50, vars->player.y * 50);

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

void    rotate_right(t_vars *vars)
{
	vars->player.angle += 0.1;
	if (vars->player.angle > 2 * PI){
		vars->player.angle -= 2 * PI;
	}
	vars->player.ray.deltadistX = cos(vars->player.angle) * 5;
	vars->player.ray.deltadistY = sin(vars->player.angle) * 5;
}
t_ray  *init(t_ray *ray)
{
	ray->y = 0;
	ray->x = 0;
	ray->plane_x = 0;
	ray->plane_y = 0;
	ray->raydirX = 0;
	ray->raydirY = 0;
	ray->sidedistY = 0;
	ray->sidedistX = 0;
	ray->deltadistY = 0;
	ray->deltadistX = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->orientation = 0;
    return (ray);
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
	vars->player.angle = 0;
    (void)argc;(void)argv;
    init(&vars->player.ray);
    vars->map = ft_split("11111111:10100011:10110001:10000W01:10100011:10100101:10100011:11111111",':');
	find_pos(vars, vars->map);
	init_orientation(vars);
	initialization(vars);
}