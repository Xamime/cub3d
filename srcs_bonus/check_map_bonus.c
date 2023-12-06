/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:16:10 by maxime            #+#    #+#             */
/*   Updated: 2023/12/06 21:24:49 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	is_not_closed(t_object **map, int start_i, int start_j)
{
	int	i;
	int	j;
	int	len_above;
	int	len_below;

	i = start_i;
	j = start_j;
	len_below = ft_line_len(map[i + 2]);
	len_above = ft_line_len(map[i]);
	if (j + 1 > len_above - 1 || j + 1 > len_below - 1)
		return (1);
	while (i < start_i + 3)
	{
		if (!map[i])
			return (1);
		j = start_j;
		while (j < start_j + 3)
		{
			if (!map[i][j].type || map[i][j].type == ' ')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_if_map_is_close(t_object **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j].type)
		{
			if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1].type)
			{
				if (map[i][j].type != '1' && map[i][j].type != ' ')
					return (1);
			}
			else if (map[i][j].type != '1' && map[i][j].type != ' '
				&& is_not_closed(map, i - 1, j - 1))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	player_count(t_object **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j].type)
		{
			if (map[i][j].type != ' ' && map[i][j].type != '1'
				&& map[i][j].type != '0' && map[i][j].type != 'D')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}
