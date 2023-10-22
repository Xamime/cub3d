/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 05:56:50 by jfarkas           #+#    #+#             */
/*   Updated: 2023/10/22 06:54:43 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	alloc_texture(t_vars *vars)
{
	vars->buffer = (uint32_t *)malloc(sizeof(int) * HEIGHT * WIDTH);
	if (vars->buffer == NULL) {
		perror("Memory allocation failed");
		return ;
	}
}

mlx_image_t	*load_texture(char *path, mlx_t *mlx)
{
	mlx_texture_t	*tmp;
	mlx_image_t		*tex;

	tmp = mlx_load_png(path);
	tex = mlx_texture_to_image(mlx, tmp);
	if(!tex)
	{
		printf("this image doesnt exist\n");
		mlx_terminate(mlx);
		exit(1);
	}
	mlx_delete_texture(tmp);
	return (tex);
}

void	init_textures(t_vars *vars)
{
	vars->textures[NORTH] = load_texture("./textures/eagle.png", vars->mlx);
	vars->textures[SOUTH] = load_texture("./textures/redbrick.png", vars->mlx);
	vars->textures[EAST] = load_texture("./textures/pillar.png", vars->mlx);
	vars->textures[WEST] = load_texture("./textures/greenlight.png", vars->mlx);
	//drawtext(vars->mlx, vars->textures[NORTH]);

	alloc_texture(vars);

	//todo free textures;
}
