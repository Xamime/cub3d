/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:32 by mdesrose          #+#    #+#             */
/*   Updated: 2023/09/26 17:27:59 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 400
#define HEIGHT 400
#define ROTATE 2.50
#define SPEED 4
#define PI 3,14159265358979

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_ray
{
	double	y;
	double	x;
	double	camerax;
	double	plane_x;
	double	plane_y;
	double	facedistY;
	double	perpwalldist;
	double	raydirx;
	double	raydiry;
	double	dirX;
	double	dirY;
	double	sidedistY;
	double	sidedistX;
	double	deltadistY;
	double	deltadistX;
	double	orientation;
	int		hit;
	int		side;
	
}		t_ray;

typedef struct	t_player
{
	mlx_image_t	*image;
	double	x;
	double	y;
	double	angle;
	char	orientation;
	t_ray	ray;
}			t_player;


typedef struct t_vars
{
	char		**map;
	mlx_image_t *minimap;
	mlx_t		*mlx;
	t_player	player;
}				t_vars;

typedef struct s_point
{
	int x;
	int y;
}		t_point;

void    draw_pixels_around(mlx_image_t *minimap, int x, int y, char **map);
void 	ft_draw_pixels_grid(void* param);
void    dda(t_vars *vars, t_point start, t_point end);
void 	ft_draw_first_player(void* param);
void	ft_draw_pixels_player(void* param);

#endif
