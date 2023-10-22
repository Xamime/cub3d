/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:32 by mdesrose          #+#    #+#             */
/*   Updated: 2023/10/22 07:09:58 by jfarkas          ###   ########.fr       */
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

#define PI 3.14159

#define WIDTH 1000
#define HEIGHT 1000
#define ROTATE 2.50
#define SPEED 4
#define texWidth 64
#define texHeight 64

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

#define RED "\e[38;2;255;0;0m"
#define ORANGE "\e[38;2;255;150;0m"
#define YELLOW "\e[38;2;255;255;0m"
#define GREEN "\e[38;2;0;255;0m"
#define BLUE "\e[38;2;150;150;255m"
#define VIOLET "\e[38;2;200;0;200m"
#define DEFAULT_COL "\e[m"

typedef struct s_ipoint
{
	int	x;
	int	y;
}				t_ipoint;

typedef struct s_fpoint
{
	float	x;
	float	y;
}				t_fpoint;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct	s_dda
{
	t_fpoint	delta_dist;
	t_ipoint	map;
	t_ipoint	step;
	int			side;
}				t_dda;


typedef struct	s_ray
{
	double		camerax;
	double		angle;
	t_fpoint	plane;
	t_fpoint	ray_dir;
	t_fpoint	dir;
	double		wall_dist;
	int			lineheight;
	int			drawstart;
	int			drawend;
}				t_ray;

typedef struct	t_player
{
	mlx_image_t	*image;
	double		x;
	double		y;
	double		angle;
	double		movespeed;
	double		rotspeed;
	char		orientation;
}				t_player;


typedef struct	s_texture
{
	//eagle
	mlx_image_t		*north;
	mlx_image_t		*south;
	//colorstone
	mlx_image_t		*west;
	//wood
	mlx_image_t		*east;
	// int				*floor;
	// int				*ceiling;
	// unsigned long	hex_floor;
	// unsigned long	hex_ceiling;
	// int				size;
	// int				index;
	// double			step;
	// double			pos;
	// int				x;
	// int				y;
}				t_tex;

typedef struct t_vars
{
	char		**map;
	t_ray		ray;
	t_dda		dda;
	mlx_image_t	*minimap;
	mlx_image_t	*game;
	uint32_t	instance;
	mlx_t		*mlx;
	t_player	player;
	mlx_image_t	*textures[4];
	// t_tex		tex;
	uint32_t	*buffer;
	char		*title;
	// int			**texture_pixels;
	// int			**textures;
}				t_vars;


int	check_wall(t_vars *vars, double x, double y);

void    draw_pixels_around(mlx_image_t *minimap, int x, int y, char **map);
void	ft_draw_walls(t_vars *vars, t_ray *ray);
void 	ft_draw_pixels_grid(void* param);
void    dda(char **map, t_ray *ray);
void 	ft_draw_first_player(void* param);
void	ft_draw_pixels_player(void* param);

/*					Initialisation					*/
void	init_img(t_img *img);
void	init(t_vars *vars);
void	init_orientation(t_vars *vars);
void	init_textures(t_vars *vars);
void    find_pos(t_vars *vars, char **map);

/*					Moving							*/
void    rotate_left(t_vars *vars, t_ray *ray);
void    rotate_right(t_vars *vars, t_ray *ray);
void	ft_up(t_vars *vars, t_ray *ray);
void	ft_down(t_vars *vars, t_ray *ray);
void	left_step(t_vars *vars, t_ray *ray);
void	right_step(t_vars *vars, t_ray *ray);

/*					Textures						*/
void	get_texture_index(t_vars *vars);
void	update_texture_pixels(t_vars *vars, t_tex *tex, t_ray *ray, int x);

/* ---------------------------------- utils --------------------------------- */

uint32_t	create_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void		float_to_char(float number, char* str, int precision);

/* ---------------------------------- debug --------------------------------- */

void	ft_display_rays(t_vars *vars, t_ray *ray);
void	ft_set_ray_dir(double *dir_x, double *dir_y, int x, t_ray *ray);

#endif
