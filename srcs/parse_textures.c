/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:47:41 by jfarkas           #+#    #+#             */
/*   Updated: 2023/11/30 13:48:58 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_textures(t_vars *vars, char *tex_paths[4])
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (i < 4)
	{
		if (!error && init_textures_test(vars, tex_paths[i], i))
			error = 1;
		free(tex_paths[i]);
		i++;
	}
	if (error)
		return (1);
	return (0);
}

int	test_tex_paths(char *tex_paths[4])
{
	int	i;
	int	fd;

	// soit ameliorer la fonction soit la degager
	i = 0;
	while (i < 4)
	{
		if (ft_strlen(tex_paths[i]) < 4
			|| ft_strcmp(&tex_paths[i][ft_strlen(tex_paths[i]) - 4], ".png"))
		{
			printf("Error\n%s: wrong texture extension\n", tex_paths[i]);
			return (1);
		}
		fd = open(tex_paths[i], O_RDONLY);
		if (fd == -1)
		{
			printf("Error\n");
			perror(tex_paths[i]);
			return (1);
		}
		else
			close(fd);
		i++;
	}
	return (0);
}
