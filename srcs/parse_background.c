/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_background.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:07:46 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/03 16:34:27 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_colors(char **colors)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ft_atoi((colors[i])) > 255 || ft_atoi((colors[i])) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	get_background(t_bg *bg, char *str, int dir)
{
	char	**colors;
	int		i;

	i = 0;
	colors = ft_split(str, ',');
	if (check_colors(colors) == -1)
	{
		free_2d_array(colors);
		return (-1);
	}
	if (dir == FLOOR)
	{
		bg->floor.r = ft_atoi(colors[0]);
		bg->floor.g = ft_atoi(colors[1]);
		bg->floor.b = ft_atoi(colors[2]);
	}
	else
	{
		bg->ceil.r = ft_atoi(colors[0]);
		bg->ceil.g = ft_atoi(colors[1]);
		bg->ceil.b = ft_atoi(colors[2]);
	}
	free_2d_array(colors);
	bg->color_set++;
	return (0);
}
