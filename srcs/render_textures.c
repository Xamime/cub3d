/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamime <xamime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:44:09 by jfarkas           #+#    #+#             */
/*   Updated: 2023/10/23 15:43:16 by xamime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static mlx_image_t	*find_tex_side(mlx_image_t *textures[4], t_ray ray, int side)
{
	if (side == 0 && ray.ray_dir.x < 0)
		return (textures[EAST]);
	else if (side == 0 && ray.ray_dir.x > 0)
		return (textures[WEST]);
	else if (side == 1 && ray.ray_dir.y < 0)
		return (textures[NORTH]);
	else
		return (textures[SOUTH]);
}

t_render_tex	set_render_texture(t_player player, t_ray ray, int side, mlx_image_t *textures[4])
{
	t_render_tex	rtex;
	double			wallX;

	if (side == 0)
		wallX = player.y + ray.wall_dist * ray.ray_dir.y;
	else
		wallX = player.x + ray.wall_dist * ray.ray_dir.x;
	wallX -= floor((wallX));

	rtex.texture = find_tex_side(textures, ray, side);

	//printf("wallx = %f\n",wallX);
	rtex.pos.x = (int)(wallX * (double)rtex.texture->width);
	if ((side == 0 && ray.ray_dir.x > 0) || (side == 1 && ray.ray_dir.y < 0))
		rtex.pos.x = rtex.texture->width - rtex.pos.x - 1;
	return (rtex);
}
