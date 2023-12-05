/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:32 by mdesrose          #+#    #+#             */
/*   Updated: 2023/12/05 13:56:10 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <fcntl.h>

#define WIDTH 1000
#define HEIGHT 1000
#define ROTATE 2.50
#define SPEED 4

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define FLOOR 4
#define CEILING 5

typedef struct	s_ipoint
{
	int	x;
	int	y;
}				t_ipoint;

typedef struct	s_fpoint
{
	double	x;
	double	y;
}				t_fpoint;

typedef struct	s_dda
{
	t_fpoint	delta_dist;
	t_fpoint	side_dist;
	t_ipoint	map;
	t_ipoint	step;
	int			side;
}				t_dda;

typedef struct	s_ray
{
	double		camerax;
	t_fpoint	ray_dir;
	double		wall_dist;
	int			lineheight;
	int			drawstart;
	int			drawend;
}				t_ray;

typedef struct	t_player
{
	t_fpoint	plane;
	t_fpoint	dir;
	double		x;
	double		y;
	double		movespeed;
	double		rotspeed;
	char		orientation;
}				t_player;

typedef struct	s_render_tex
{
	mlx_image_t	*texture;
	t_ipoint	pos;
}				t_render_tex;

typedef struct	s_color
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
}				t_color;

typedef struct	s_bg
{
	t_color	ceil;
	t_color	floor;
	int		color_set;
}				t_bg;

typedef struct t_vars
{
	char		**map;
	mlx_image_t	*game;
	mlx_t		*mlx;
	t_player	player;
	mlx_image_t	*textures[4];
	uint32_t	*buffer;
}				t_vars;

/* -------------------------------- check_map ------------------------------- */

int				is_in_set(char c, char *charset);
int				check_if_map_is_close(char **map);
int				multiple_player(char **map);

/* ----------------------------------- dda ---------------------------------- */

double			get_wall_dist(t_player player, t_fpoint ray_dir, t_dda *dda, char **map);
t_dda			init_dda(t_player player, t_fpoint ray_dir);

/* ------------------------------- draw_utils ------------------------------- */

int				get_pixel_color(int i, int j, mlx_image_t *map_img);
void			set_ray_draw_pos(t_ray *ray);

/* ---------------------------------- draw ---------------------------------- */

void			draw_wall(t_ray ray, t_render_tex rtex, int x, uint32_t *buffer);
void			draw_buffer(mlx_image_t *game, uint32_t *buffer);

/* ---------------------------------- init ---------------------------------- */

void			init_buffer(t_vars *vars);
void			init_orientation(t_vars *vars);
void			find_pos(t_vars *vars, char **map);

/* --------------------------------- moving --------------------------------- */

void			move(t_player *player, char **map, int up);
void			rotate(t_player *player, double speed, int left);
void			side_step(t_player *player, char **map, int left);

/* ---------------------------- parse_background ---------------------------- */

int				get_background(t_bg *bgrd, char *str, int dir);

/* -------------------------------- parse_map -------------------------------- */

int				is_map(char *str);
char			*get_map(int fd, char *str);

/* ----------------------------- parse_textures ----------------------------- */

char			*get_textures(int fd, char *tex_paths[4], t_bg *bgrd);

/* --------------------------------- parsing -------------------------------- */

int				parse_file(t_vars *vars, const char *path, t_bg *bgrd);

/* ----------------------------- render_textures ---------------------------- */

t_render_tex	set_render_texture(t_player player, t_ray ray, int side, mlx_image_t *textures[4]);

/* -------------------------------- textures -------------------------------- */

int				load_textures(t_vars *vars, char *tex_paths[4]);
void			alloc_buffer(t_vars *vars);

/* ---------------------------------- utils --------------------------------- */

void			display_background(mlx_t *mlx, t_bg bgrd);
void			free_2d_array(char **str);
uint32_t		create_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void			free_map(char **map);
int				ft_line_len(char *line);

/* --------------------------------- utils2 --------------------------------- */

void			replace_address(char **addr1, char *addr2);
void			remove_endl(char *str);

/* --------------------------------- utils3 --------------------------------- */

int				test_tex_paths(char *tex_paths[4]);
void			free_tex_paths(char *tex_paths[4]);
int				check_count(char *tex_paths[4], t_bg *bg);

#endif
