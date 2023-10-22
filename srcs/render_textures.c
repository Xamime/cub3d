/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:44:09 by jfarkas           #+#    #+#             */
/*   Updated: 2023/10/22 16:34:43 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static mlx_image_t	*find_tex_side(mlx_image_t *textures[4], int wallx, int side)
{
	(void)wallx;
	if (side == 0)
		return (textures[EAST]);
	if (side)
		return (textures[WEST]);
	return (textures[NORTH]);
}

t_render_tex	set_render_texture(t_player player, t_ray ray, int side, mlx_image_t *textures[4])
{
	//texturing calculations
	//int texNum = vars->map[dda->map.y][dda->map.x] - 1 - 48; //1 subtracted from it so that texture 0 can be used!
	//calculate value of wallX
	t_render_tex	rtex;
	double			wallX; // where exactly the wall was hit

	if (side == 0)
		wallX = player.y + ray.wall_dist * ray.ray_dir.y;
	else
		wallX = player.x + ray.wall_dist * ray.ray_dir.x;
	wallX -= floor((wallX));

	rtex.texture = find_tex_side(textures, wallX, side);

	//printf("wallx = %f\n",wallX);
	rtex.pos.x = (int)(wallX * (double)rtex.texture->width);
	if ((side == 0 && ray.ray_dir.x > 0) || (side == 1 && ray.ray_dir.y < 0))
		rtex.pos.x = rtex.texture->width - rtex.pos.x - 1;
	return (rtex);
}
