/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:44:09 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/05 19:11:50 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static mlx_image_t	*find_tex_side(mlx_image_t *textures[4], t_ray ray, int side)
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

t_render_tex	set_render_texture(t_player player, t_ray ray,
	t_dda *dda, mlx_image_t *textures[4])
{
	t_render_tex	rtex;
	double			wallX;

	printf("width : %d\n", textures[2]->width);


	if (dda->side == 0)
		wallX = player.y + ray.wall_dist * ray.ray_dir.y;
	else
		wallX = player.x + ray.wall_dist * ray.ray_dir.x;
	wallX -= floor(wallX);
	wallX = 1.0f - wallX;

	if (dda->hit.type == 'D')
		wallX -= 1.0f - player.door_status;

	rtex.texture = find_tex_side(textures, ray, dda->side);
	// printf("(tex) wallx : %f, wall_dist : %f\n", wallX, ray.wall_dist);
	// printf("(tex) ray_dir.y : %f\n", ray.ray_dir.y);
	rtex.pos.x = (int)(wallX * (double)rtex.texture->width);
	if ((dda->side == 0 && ray.ray_dir.x > 0) || (dda->side == 1 && ray.ray_dir.y < 0))
		rtex.pos.x = rtex.texture->width - rtex.pos.x - 1;
	return (rtex);
}
