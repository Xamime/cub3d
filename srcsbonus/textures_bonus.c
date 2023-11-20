/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 05:56:50 by jfarkas           #+#    #+#             */
/*   Updated: 2023/11/20 15:20:56 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	alloc_buffer(t_vars *vars)
{
	vars->buffer = (uint32_t *)malloc(sizeof(int) * HEIGHT * WIDTH);
	if (vars->buffer == NULL)
	{
		perror("Memory allocation failed");
		return ;
	}
}

void	free_images(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 4 && vars->textures[i])
	{
		free(vars->textures[i]);
		i++;
	}
}

mlx_image_t	*load_texture(t_vars *vars, char *path, mlx_t *mlx)
{
	mlx_texture_t	*tmp;
	mlx_image_t		*tex;

	tmp = mlx_load_png(path);
	if (!tmp)
	{
		mlx_terminate(mlx);
		exit(1);
	}
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

void	init_textures_test(t_vars *vars, char *path, int direction)
{
	int i = 0;
	while (path[i])
	{
		if (path[i] == '\n')
			path[i] = '\0';
		i++;
	}
	vars->textures[direction] = load_texture(vars, path, vars->mlx);
	//todo free textures;
}
