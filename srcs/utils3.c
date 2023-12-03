/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:27:01 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/03 21:24:37 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	test_tex_paths(char *tex_paths[4])
{
	int	i;
	int	fd;

	i = 0;
	while (i < 4)
	{
		if (ft_strlen(tex_paths[i]) < 4
			|| ft_strcmp(&tex_paths[i][ft_strlen(tex_paths[i]) - 4], ".png"))
		{
			printf("Error\nInvalid texture\n");
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

int	check_count(char *tex_paths[4], t_bg *bg)
{
	int	i;

	i = 0;
	while (tex_paths[i] && i < 4)
		i++;
	if (i < 3 || bg->color_set != 2)
	{
		if (i < 3)
			printf("Error\nA texture is missing\n");
		else if (bg->color_set != 2)
			printf("Error\nA color is missing\n");
		return (1);
	}
	return (0);
}
