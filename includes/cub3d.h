/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:32 by mdesrose          #+#    #+#             */
/*   Updated: 2023/10/31 17:00:53 by jfarkas          ###   ########.fr       */
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

//open files
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

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
#define FLOOR 4
#define CEILING 5
#define MAP 6

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
	t_fpoint	ray_dir;
	double		wall_dist;
	int			lineheight;
	int			drawstart;
	int			drawend;
}				t_ray;

typedef struct	t_player
{
	mlx_image_t	*image;
	t_fpoint	plane;
	t_fpoint	dir;
	double		x;
	double		y;
	double		angle;
	double		movespeed;
	double		rotspeed;
	char		orientation;
	int			has_moved;
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
}				t_tex;

typedef struct	s_render_tex
{
	mlx_image_t	*texture;
	t_ipoint	pos;
}				t_render_tex;

typedef struct	s_rgb
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
}				t_rgb;

typedef struct	s_background
{
	t_rgb	ceil;
	t_rgb	floor;
}				t_bgrd;


typedef struct t_vars
{
	char		**map;
	t_ray		*ray;
	mlx_image_t	*minimap;
	double		case_size;
	mlx_image_t	*game;
	mlx_image_t	*screen;
	uint32_t	instance;
	mlx_image_t	*instance2;
	mlx_t		*mlx;
	t_player	player;
	mlx_image_t	*textures[4];
	uint32_t	*buffer;
	char		*title;
	int			start;
}				t_vars;


void	init_textures_test(t_vars *vars, char *path, int direction);
int	check_wall(t_vars *vars, double x, double y);
void	find_path_tex(t_vars *vars, char *str, t_bgrd *bgrd, char **to_split);

int		parse_file(t_vars *vars, const char *path, t_bgrd *bgrd);
void	alloc_texture(t_vars *vars);
void    draw_pixels_around(mlx_image_t *minimap, int x, int y, char **map);
t_ray	update_buffer(t_player *player, char **map, mlx_image_t *textures[4], uint32_t *buffer);
void 	ft_draw_pixels_grid(void* param);
void    dda(char **map, t_ray *ray);
void 	ft_draw_first_player(void* param);
void	ft_draw_pixels_player(void* param, t_ray ray);
void	draw_minimap(t_vars *vars);

/*					Initialisation					*/
void	init_img(t_img *img);
void	init(t_vars *vars);
void	init_orientation(t_vars *vars);
void	init_textures(t_vars *vars);
void    find_pos(t_vars *vars, char **map);

/*					Moving							*/
void    rotate_left(t_player *player, double speed);
void    rotate_right(t_player *player, double speed);
void	ft_up(t_player *player, char **map);
void	ft_down(t_player *player, char **map);
void	left_step(t_player *player, char **map);
void	right_step(t_player *player, char **map);

/*					Textures						*/
void	get_texture_index(t_vars *vars);
void	update_texture_pixels(t_vars *vars, t_tex *tex, t_ray *ray, int x);

/* ----------------------------------- dda ---------------------------------- */

double	get_wall_dist(t_player player, t_fpoint ray_dir, t_dda *dda, char **map);
t_dda	init_dda(t_player player, t_fpoint ray_dir);

/* ---------------------------------- draw ---------------------------------- */

void	draw_ceiling(uint32_t *buffer, int x, int y);
void	draw_floor(uint32_t *buffer, int x, int y);
void	draw_wall(t_ray ray, t_render_tex rtex, int x, uint32_t *buffer);
void	draw_buffer(t_vars *vars, mlx_image_t *game, uint32_t *buffer);

/* ------------------------------- draw_utils ------------------------------- */

int		get_pixel_color(int i, int j, mlx_image_t *map_img);
void	set_ray_draw_pos(t_ray *ray);

/* ----------------------------- render_textures ---------------------------- */

t_render_tex	set_render_texture(t_player player, t_ray ray, int side, mlx_image_t *textures[4]);

/* ---------------------------------- utils --------------------------------- */

uint32_t	create_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void		display_background(mlx_t *mlx, t_bgrd bgrd);
char		*ft_itoa_no_malloc(int n, char *str);

/* ---------------------------------- debug --------------------------------- */

void	ft_display_rays(t_vars *vars, t_ray *ray);
void	ft_set_ray_dir(double *dir_x, double *dir_y, int x, t_ray *ray);

#endif
