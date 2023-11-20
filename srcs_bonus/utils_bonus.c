/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 07:07:48 by jfarkas           #+#    #+#             */
/*   Updated: 2023/11/13 17:56:41 by jfarkas          ###   ########.fr       */
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

static int	ft_size(long long nb)
{
	long long	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_no_malloc(int n, char *str)
{
	long long	i;
	long long	nbr;

	nbr = n;
	i = ft_size(nbr);
	if (str == NULL)
		return (NULL);
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	str[i] = '\0';
	while (nbr > 0)
	{
		str[i - 1] = 48 + (nbr % 10);
		nbr = nbr / 10;
		i--;
	}
	return (str);
}
