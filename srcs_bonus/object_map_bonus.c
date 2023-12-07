/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:50:53 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/07 18:52:43 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static t_object	**malloc_map(char **split)
{
	t_object	**map;
	int			lines_nb;
	int			line;

	lines_nb = 0;
	while (split[lines_nb])
		lines_nb++;
	map = malloc(sizeof(t_object *) * (lines_nb + 1));
	if (!map)
		return (NULL);
	map[lines_nb] = NULL;
	line = 0;
	while (split[line])
	{
		map[line] = malloc(sizeof(t_object) * (ft_strlen(split[line]) + 1));
		if (!map[line])
			return (NULL);
		map[line][ft_strlen(split[line])].type = 0;
		line++;
	}
	return (map);
}

t_object	**char_to_obj_map(char **split)
{
	t_object	**map;
	int			x;
	int			y;

	map = NULL;
	map = malloc_map(split);
	if (!map)
		return (NULL);
	y = 0;
	while (split[y])
	{
		x = 0;
		while (split[y][x])
		{
			map[y][x].type = split[y][x];
			x++;
		}
		y++;
	}
	free_2d_array(split);
	return (map);
}
