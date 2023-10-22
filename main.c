/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:04 by mdesrose          #+#    #+#             */
/*   Updated: 2023/10/22 04:04:29 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

// void	my_pixel_put(t_vars *vars, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = vars->addr + (y * data->line_length + x * (32 / 8));
// 	*(unsigned int *)dst = color;
// }

static void	draw_ceiling(t_vars *vars, int x, int y)
{
	int	y1;

	y1 = 0;
	while (y1 < y)
	{
		vars->buffer[y1 * WIDTH + x] = create_rgba(150, 150, 70, 255);
		//mlx_put_pixel(vars->game, x, y1, create_rgba(150, 150, 70, 255));
		y1++;
	}
}

static void	draw_floor(t_vars *vars, int x, int y)
{
	while (y < HEIGHT)
	{
		vars->buffer[y * WIDTH + x] = create_rgba(50, 50, 140, 255);
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
	
    for (int y = y1; y <= y2; y++) {
        mlx_put_pixel(vars->game, x, y, color);
    }
	
}

mlx_image_t	*find_tex_side(t_vars *vars, int wallx)
{
	(void)wallx;
	if (vars->ray.side == 0)
		return (vars->tex.east);
	if (vars->ray.side)
		return (vars->tex.west);
	return (vars->tex.north);
}

void drawBuffer(t_vars *vars, mlx_image_t *game, uint32_t *buffer)	
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            mlx_put_pixel(game, x, y, buffer[y * WIDTH + x]) ;
        }
    }
	mlx_image_to_window(vars->mlx, game, 0, 0);
}

int    retrieve_pixel_color(int i, int j, mlx_image_t *map_img)
{
    int    width;
    int    *pixel_color;
    int    rgb[3];

    width = map_img->width;
    pixel_color = (int *)map_img->pixels + (j * width + i);
    rgb[0] = (*pixel_color << 8) >> 24 & 0xFF;
    rgb[1] = (*pixel_color << 16) >> 24 & 0xFF;
    rgb[2] = (*pixel_color << 24) >> 24 & 0xFF;
    return (rgb[0] << 8 | rgb[1] << 16 | rgb[2] << 24 | 255);
}

void	 ft_draw_walls(t_vars *vars, t_ray *ray)
{
	uint32_t	color;
	init(vars);
	//reset_window(vars);
	if (vars->game)
		mlx_delete_image(vars->mlx,vars->game);

	vars->game = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			vars->buffer[y * WIDTH + x] = 0;
		}
	}
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
		//texturing calculations
		//int texNum = vars->map[ray->mapy][ray->mapx] - 1 - 48; //1 subtracted from it so that texture 0 can be used!
      	//calculate value of wallX
     	double wallX; //where exactly the wall was hit
     	if (ray->side == 0)
			wallX = vars->player.y + ray->perpwalldist * ray->raydiry;
     	else
			wallX = vars->player.x + ray->perpwalldist * ray->raydirx;
     	wallX -= floor((wallX));
		//printf("wallx = %f\n",wallX);
     	//x coordinate on the texture
     	int texX = (int)(wallX * (double)texWidth);
     	if(ray->side == 0 && ray->raydirx > 0)
			texX = texWidth - texX - 1;
     	if(ray->side == 1 && ray->raydiry < 0)
			texX = texWidth - texX - 1;
		// How much to increase the texture coordinate per screen pixel
    	double step = 1.0 * texHeight / ray->lineheight;
    	// Starting texture coordinate
    	double texPos = (ray->drawstart - HEIGHT / 2 + ray->lineheight / 2) * step;
		draw_ceiling(vars,x,vars->ray.drawstart);
		draw_floor(vars, x, ray->drawend);
    	for(int y = ray->drawstart; y < ray->drawend; y++)
    	{
        	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        	int texY = (int)texPos & (texHeight - 1);
        	texPos += step;
        	color = retrieve_pixel_color(texX,texY,find_tex_side(vars, wallX));
        	vars->buffer[y * WIDTH + x] = color;
    	}
	}
	drawBuffer(vars, vars->game, vars->buffer);
	vars->player.movespeed = vars->mlx->delta_time * 5.0;
	vars->player.rotspeed = vars->mlx->delta_time * 3.0;
	// ft_display_rays(vars, ray);
}

void ft_hook(void* param)
{
	t_vars *vars  = param;

	//ft_draw_pixels_grid(vars);
	//ft_draw_pixels_player(vars);
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
	//printf("fps = %f\n", 1.0 / vars->mlx->delta_time);
	char *str = NULL;
	str = malloc(sizeof(char) * 20);
	floatToChar((1.0 / vars->mlx->delta_time), str, 1);
	str = ft_strjoin(str, " FPS");
	mlx_set_window_title(vars->mlx, str);
	free(str);
}

void	alloc_texture(t_vars *vars)
{
	vars->buffer = (uint32_t *)malloc(sizeof(int) * HEIGHT * WIDTH);
	if (vars->buffer == NULL) {
        perror("Memory allocation failed");
        exit(1) ;
    }
}

void	load_texture(t_vars *vars)
{
	mlx_texture_t *tes;
	tes = mlx_load_png("./textures/eagle.png");
	vars->tex.north = mlx_texture_to_image(vars->mlx, tes);
	if(!vars->tex.north)
	{
		printf("this image doesnt exist\n");
		exit(1);
	}
	tes = mlx_load_png("./textures/redbrick.png");
	vars->tex.south = mlx_texture_to_image(vars->mlx, tes);
	if(!vars->tex.south)
	{
		printf("this image doesnt exist\n");
		exit(1);
	}
	tes = mlx_load_png("./textures/wood.png");
	vars->tex.east = mlx_texture_to_image(vars->mlx, tes);
	if(!vars->tex.east)
	{
		printf("this image doesnt exist\n");
		exit(1);
	}
	tes = mlx_load_png("./textures/colorstone.png");
	vars->tex.west = mlx_texture_to_image(vars->mlx, tes);
	if(!vars->tex.west)
	{
		printf("this image doesnt exist\n");
		exit(1);
	}	
	mlx_delete_texture(tes);
	//todo free textures;
}

int    start_loop(t_vars *vars)
{
	vars->mlx = mlx_init(WIDTH, HEIGHT, "cub", true);
	load_texture(vars);
	alloc_texture(vars);
	//reset_window(vars);
	ft_draw_walls(vars, &vars->ray);
	mlx_loop_hook(vars->mlx, ft_hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}


int main(int32_t argc, const char* argv[])
{
	t_vars	vars;

	(void)argc;(void)argv;
	//system("clear");
	init(&vars);
	vars.map = ft_split("11111111:10000001:10000001:1010S001:10000001:10000001:10000001:11111111",':');
	find_pos(&vars, vars.map);
	init_orientation(&vars);
	start_loop(&vars);
	for (int i = 0; vars.map[i]; i++)
		free(vars.map[i]);
	free(vars.map);
	free(vars.buffer);
	return (EXIT_SUCCESS);
}
