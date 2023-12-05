/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:16:10 by maxime            #+#    #+#             */
/*   Updated: 2023/12/05 20:25:22 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_in_set(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	is_not_closed(char **map, int start_i, int start_j)
{
	int	i;
	int	j;
	int	len_above;
	int	len_below;

	i = start_i;
	j = start_j;
	len_below = (int)ft_strlen(map[i+ 2]);
	len_above = (int)ft_strlen(map[i]);
	if (j + 1 > len_above - 1 || j + 1 > len_below - 1)
		return (1);
	while (i < start_i + 3)
	{
		if (!map[i])
			return (1);
		j = start_j;
		while (j < start_j + 3)
		{
			if (is_in_set(map[i][j], " \0"))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_if_map_is_close(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1])
			{
				if (map[i][j] != '1' && map[i][j] != ' ')
					return (1);
			}
			else if (map[i][j] != '1' && map[i][j] != ' ' && is_not_closed(map, i - 1, j - 1))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	player_count(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}
