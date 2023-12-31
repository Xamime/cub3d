/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 07:07:48 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/06 21:48:30 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	display_background(mlx_t *mlx, t_bg bg)
{
	mlx_image_t	*background;
	int			x;
	int			y;

	background = mlx_new_image(mlx, WIDTH, HEIGHT);
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(background, x, y, create_rgba(bg.ceil.r,
						bg.ceil.g, bg.ceil.b, 255));
			else
				mlx_put_pixel(background, x, y, create_rgba(bg.floor.r,
						bg.floor.g, bg.floor.b, 255));
			y++;
		}
		x++;
	}
	mlx_image_to_window(mlx, background, 0, 0);
}

void	free_2d_array(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_map(t_object **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	ft_line_len(t_object *line)
{
	int	i;

	i = 0;
	while (line && line[i].type)
		i++;
	return (i);
}

uint32_t	create_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
