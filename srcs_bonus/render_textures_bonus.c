/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:44:09 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/07 19:51:56 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static mlx_image_t	*find_tex_side(mlx_image_t *textures[4],
		t_ray ray, int side)
{
	if (side == 0 && ray.ray_dir.x < 0)
		return (textures[EAST]);
	else if (side == 0 && ray.ray_dir.x > 0)
		return (textures[WEST]);
	else if (side == 1 && ray.ray_dir.y < 0)
		return (textures[SOUTH]);
	else if (side == 1 && ray.ray_dir.y > 0)
		return (textures[NORTH]);
	return (NULL);
}

t_rtex	set_render_texture(t_player player, t_ray ray,
	t_dda *dda, mlx_image_t *textures[4])
{
	t_rtex	rtex;
	double	wallx;

	if (dda->side == 0)
		wallx = player.y + ray.wall_dist * ray.ray_dir.y;
	else
		wallx = player.x + ray.wall_dist * ray.ray_dir.x;
	wallx -= floor(wallx);
	wallx = 1.0f - wallx;
	if (dda->hit->type == 'D')
		wallx -= 1.0f - dda->hit->status;
	if (wallx < 0.0f)
		wallx = 0.0f;
	rtex.texture = find_tex_side(textures, ray, dda->side);
	rtex.pos.x = (int)(wallx * (double)rtex.texture->width);
	if ((dda->side == 0 && ray.ray_dir.x > 0)
		|| (dda->side == 1 && ray.ray_dir.y < 0))
		rtex.pos.x = rtex.texture->width - rtex.pos.x - 1;
	return (rtex);
}
