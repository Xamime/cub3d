/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:32 by mdesrose          #+#    #+#             */
/*   Updated: 2023/12/07 16:40:32 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <fcntl.h>

#define WIDTH 1000
#define HEIGHT 1000
#define ROTATE 2.50
#define SPEED 4
#define MINIMAP_SIZE 200
#define MINIMAP_PLAYER_SIZE 5

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define FLOOR 4
#define CEILING 5

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

#define NS 0
#define WE 1

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

typedef struct	s_object
{
	char	type;
	int		orientation;
	double	mode;
	double	timer;
}				t_object;

typedef struct s_door_collision
{
	double	wall_y;
	double	next_wall_y;
	double	door_x;
	double	door_y;
	double	ray_dir;
	double	next_side_dist;
	int		next_side;
	int		door_axis;
}				t_door_collision;


typedef struct	s_dda
{
	t_fpoint	delta_dist;
	t_fpoint	side_dist;
	t_ipoint	map;
	t_ipoint	step;
	int			side;
	t_object	*hit;
	t_object	*first_door;
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
	double		move_speed;
	double		rot_speed;
	char		orientation;
	t_object	*aimed_obj;
	int			door_opening;
	int			door_closing;
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
	t_object	**map;
	mlx_image_t	*game;
	mlx_image_t	*minimap;
	mlx_image_t	*crosshair;
	mlx_t		*mlx;
	t_player	player;
	mlx_image_t	*textures[4];
	uint32_t	*buffer;
	double		time;
	double		case_size;
}				t_vars;

/* -------------------------------- check_map ------------------------------- */

int				check_if_map_is_close(t_object **map);
int				player_count(t_object **map);

/* ----------------------------------- dda ---------------------------------- */

int				collide_with_door(t_dda *dda, t_player player, t_fpoint ray_dir);
double			get_wall_dist(t_player *player, t_fpoint ray_dir, t_dda *dda, t_object **map);
t_dda			init_dda(t_player player, t_fpoint ray_dir);

/* ----------------------------- door_collisions ---------------------------- */

int				check_all_cases(t_door_collision *dc, t_dda *dda, t_player player, t_fpoint ray_dir);

/* ---------------------------------- doors --------------------------------- */

double			wall_hitpos(double player_pos, double side_dist, double ray_dir);
int				collide_with_door(t_dda *dda, t_player player, t_fpoint ray_dir);

/* ---------------------------------- draw ---------------------------------- */

void			draw_crosshair(mlx_image_t *crosshair);
void			draw_wall(t_ray ray, t_render_tex rtex, int x, uint32_t *buffer);
void			draw_buffer(mlx_image_t *game, uint32_t *buffer);

/* ------------------------------ draw_minimap ------------------------------ */

void			draw_minimap(t_vars *vars);

/* ------------------------------- draw_utils ------------------------------- */

int				get_pixel_color(int i, int j, mlx_image_t *map_img);
void			set_ray_draw_pos(t_ray *ray);

/* ---------------------------------- hooks --------------------------------- */

void			main_hook(void* param);
void			cursor_hook(double x, double y, void *param);

/* ---------------------------------- init ---------------------------------- */

void			init(t_vars *vars, t_bg *bg);
void			init_buffer(uint32_t *buffer);

/* ---------------------------------- init2 --------------------------------- */

void			init_vars(t_vars *vars);
void			init_objects(t_vars *vars, t_object **map);

/* ---------------------------------- main ---------------------------------- */

void			update_buffer(t_player *player, t_object **map, mlx_image_t *textures[4], uint32_t *buffer);

/* --------------------------------- moving --------------------------------- */

void			move(t_player *player, t_object **map, int dir);
void			rotate(t_player *player, double speed);

/* ---------------------------- parse_background ---------------------------- */

int				get_background(t_bg *bg, char *str, int dir);

/* -------------------------------- parse_map -------------------------------- */

int				is_map(char *str);
char			*get_map(int fd, char *str);

/* ----------------------------- parse_textures ----------------------------- */

char			*get_textures(int fd, char *tex_paths[4], t_bg *bg);

/* --------------------------------- parsing -------------------------------- */

int				parse_file(t_vars *vars, const char *path, t_bg *bg);

/* ----------------------------- render_textures ---------------------------- */

t_render_tex	set_render_texture(t_player player, t_ray ray, t_dda *dda, mlx_image_t *textures[4]);

/* -------------------------------- textures -------------------------------- */

void			alloc_buffer(t_vars *vars);
int				load_textures(t_vars *vars, char *tex_paths[4]);

/* ---------------------------------- utils --------------------------------- */

void			display_background(mlx_t *mlx, t_bg bg);
void			free_2d_array(char **str);
uint32_t		create_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void			free_map(t_object **map);
int				ft_line_len(t_object *line);

/* --------------------------------- utils2 --------------------------------- */

void			replace_address(char **addr1, char *addr2);
void			remove_endl(char *str);
int				set_texture(int id, char **tmp, char *str, char *tex_paths[4]);
int				is_empty_line(char *str);

/* --------------------------------- utils3 --------------------------------- */

int				test_tex_paths(char *tex_paths[4]);
void			free_tex_paths(char *tex_paths[4]);
int				check_count(char *tex_paths[4], t_bg *bg);
int				get_mapsize(t_vars *vars);

#endif
