/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_background_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:07:46 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/05 16:44:42 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_color(char **color)
{
	int	i;

	i = 0;
	while (color && color[i] && color[i][0])
	{
		if (ft_atoi((color[i])) > 255 || ft_atoi((color[i])) < 0
			|| !str_isdigit(color[i]))
			return (1);
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

static void	set_rgb(t_color *color, char **rgb)
{
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
}

int	get_background(t_bg *bg, char *str, int dir)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (rgb && rgb[0] && rgb[1] && rgb[2])
		remove_endl(rgb[2]);
	if (check_color(rgb))
	{
		printf("Error\nInvalid color\n");
		free_2d_array(rgb);
		return (1);
	}
	if (dir == FLOOR)
		set_rgb(&bg->floor, rgb);
	else
		set_rgb(&bg->ceil, rgb);
	free_2d_array(rgb);
	bg->color_set++;
	return (0);
}
