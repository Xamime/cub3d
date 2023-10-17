/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:32 by mdesrose          #+#    #+#             */
/*   Updated: 2023/10/17 07:17:53 by jfarkas          ###   ########.fr       */
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

#define WIDTH 1000
#define HEIGHT 1000
#define ROTATE 2.50
#define SPEED 4
#define PI 3,14159265358979

#define RED "\e[38;2;255;0;0m"
#define ORANGE "\e[38;2;255;150;0m"
#define YELLOW "\e[38;2;255;255;0m"
#define GREEN "\e[38;2;0;255;0m"
#define BLUE "\e[38;2;150;150;255m"
#define VIOLET "\e[38;2;200;0;200m"
#define DEFAULT_COL "\e[m"

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_ray
{
	double	camerax;
	double	angle;
	double	plane_x;
	double	plane_y;
	double	perpwalldist;
	double	raydirx;
	double	raydiry;
	double	dirx;
	double	diry;
	double	sidedisty;
	double	sidedistx;
	double	deltadisty;
	double	deltadistx;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		hit;
	int		side;

}		t_ray;

typedef struct	t_player
{
	mlx_image_t	*image;
	double	x;
	double	y;
	double	angle;
	double	movespeed;
	double	rotspeed;
	char	orientation;
}			t_player;


typedef struct	s_texture
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}				t_texture;

typedef struct t_vars
{
	char		**map;
	t_ray		ray;
	mlx_image_t *minimap;
	mlx_image_t *game;
	mlx_t		*mlx;
	t_player	player;
	t_texture	texture;
	char		*title;
	int			**texture_pixels;
	int			**textures;
}				t_vars;

typedef struct s_point
{
	int x;
	int y;
}		t_point;

int	check_wall(t_vars *vars, double x, double y);

void    draw_pixels_around(mlx_image_t *minimap, int x, int y, char **map);
void 	ft_draw_pixels_grid(void* param);
void    dda(char **map, t_ray *ray);
void 	ft_draw_first_player(void* param);
void	ft_draw_pixels_player(void* param);

/*					Initialisation					*/
void	init_img(t_img *img);
void	init(t_vars *vars);
void	init_orientation(t_vars *vars);
void	init_textures(t_texture *textures);

/*					Moving							*/
void    rotate_left(t_vars *vars, t_ray *ray);
void    rotate_right(t_vars *vars, t_ray *ray);
void	ft_up(t_vars *vars, t_ray *ray);
void	ft_down(t_vars *vars, t_ray *ray);
void	left_step(t_vars *vars, t_ray *ray);
void	right_step(t_vars *vars, t_ray *ray);

/*					Textures						*/
void	get_texture_index(t_vars *vars);
void	update_texture_pixels(t_vars *vars, t_texture *tex, t_ray *ray, int x);

/* ---------------------------------- utils --------------------------------- */

int		create_argb(int a, int r, int g, int b);

/* ---------------------------------- debug --------------------------------- */

void	ft_display_rays(t_vars *vars, t_ray *ray);

#endif
