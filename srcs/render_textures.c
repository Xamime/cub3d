/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:44:09 by jfarkas           #+#    #+#             */
/*   Updated: 2023/11/22 18:29:38 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static mlx_image_t	*find_tex_side(mlx_image_t *tex[4], t_ray ray, int side)
{
	if (side == 0 && ray.ray_dir.x < 0)
		return (tex[EAST]);
	else if (side == 0 && ray.ray_dir.x > 0)
		return (tex[WEST]);
	else if (side == 1 && ray.ray_dir.y < 0)
		return (tex[SOUTH]);
	else if (side == 1 && ray.ray_dir.y > 0)
		return (tex[NORTH]);
	return (NULL);
}

t_render_tex	set_render_texture(t_player player, t_ray ray,
	int side, mlx_image_t *textures[4])
{
	t_render_tex	rtex;
	double			wallx;

	if (side == 0)
		wallx = player.y + ray.wall_dist * ray.ray_dir.y;
	else
		wallx = player.x + ray.wall_dist * ray.ray_dir.x;
	wallx -= floor(wallx);
	wallx = 1.0f - wallx;
	rtex.texture = find_tex_side(textures, ray, side);
	rtex.pos.x = (int)(wallx * (double)rtex.texture->width);
	if ((side == 0 && ray.ray_dir.x > 0) || (side == 1 && ray.ray_dir.y < 0))
		rtex.pos.x = rtex.texture->width - rtex.pos.x - 1;
	return (rtex);
}
