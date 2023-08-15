/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:32 by mdesrose          #+#    #+#             */
/*   Updated: 2023/08/15 19:36:02 by mdesrose         ###   ########.fr       */
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
	double	plane_x;
	double	plane_y;
	double	raydirX;
	double	raydirY;
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
void	 ft_draw_pixels_player(void* param);

#endif
