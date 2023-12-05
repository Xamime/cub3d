/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:27:01 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/05 18:10:10 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	test_tex_paths(char *tex_paths[4])
{
	int	i;
	int	fd;

	i = 0;
	while (i < 4)
	{
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

void	free_tex_paths(char *tex_paths[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(tex_paths[i]);
		i++;
	}
}

int	check_count(char *tex_paths[4], t_bg *bg)
{
	int	i;

	i = 0;
	while (tex_paths[i] && i < 4)
		i++;
	if (i < 3 || bg->color_set != 2)
	{
		if (i < 3)
			printf("Error\nNot enough textures\n");
		else if (bg->color_set < 2)
			printf("Error\nNot all background colors are set\n");
		else if (bg->color_set > 2)
			printf("Error\nBackground colors can't be set multiple times\n");
		return (1);
	}
	return (0);
}
