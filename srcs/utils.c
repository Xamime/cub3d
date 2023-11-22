/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 07:07:48 by jfarkas           #+#    #+#             */
/*   Updated: 2023/11/22 18:21:34 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	display_background(mlx_t *mlx, t_bgrd bgrd)
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
				mlx_put_pixel(background, x, y, create_rgba(bgrd.ceil.r,
						bgrd.ceil.g, bgrd.ceil.b, 255));
			else
				mlx_put_pixel(background, x, y, create_rgba(bgrd.floor.r,
						bgrd.floor.g, bgrd.floor.b, 255));
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
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

uint32_t	create_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	free_map(char **map)
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

int	ft_line_len(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
		i++;
	return (i);
}
