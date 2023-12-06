/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 05:56:50 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/06 15:09:11 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	alloc_buffer(t_vars *vars)
{
	vars->buffer = (uint32_t *)malloc(sizeof(int) * HEIGHT * WIDTH);
	if (vars->buffer == NULL)
	{
		mlx_terminate(vars->mlx);
		perror("Memory allocation failed");
		return ;
	}
}

static mlx_image_t	*load_texture(char *path, mlx_t *mlx)
{
	mlx_texture_t	*tmp;
	mlx_image_t		*tex;

	tmp = mlx_load_png(path);
	if (!tmp)
	{
		printf("Error\n%s: can't use as a texture\n", path);
		return (NULL);
	}
	tex = mlx_texture_to_image(mlx, tmp);
	if (!tex)
	{
		printf("Error\n%s: can't convert to an image\n", path);
		return (NULL);
	}
	mlx_delete_texture(tmp);
	return (tex);
}

static int	init_textures(t_vars *vars, char *path, int direction)
{
	vars->textures[direction] = load_texture(path, vars->mlx);
	if (!vars->textures[direction])
	{
		mlx_terminate(vars->mlx);
		return (1);
	}
	return (0);
}

int	load_textures(t_vars *vars, char *tex_paths[4])
{
	int	i;
	int	error_status;

	i = 0;
	error_status = 0;
	while (i < 4)
	{
		if (!error_status && init_textures(vars, tex_paths[i], i))
			error_status = 1;
		free(tex_paths[i]);
		i++;
	}
	return (error_status);
}
