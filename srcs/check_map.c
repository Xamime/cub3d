/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:16:10 by maxime            #+#    #+#             */
/*   Updated: 2023/12/03 16:02:31 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_in_set(char c, char *charset)
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

static int	check_side_char(char **map, int i, int j)
{
	if (map[i][j] == '0' && (j == 0 || i == 0 || !map[i + 1] || !map[i][j + 1]))
	{
		return (1);
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
			if (i == 0 || j == 0 || map[i + 1] == NULL
				|| map[i][j + 1] == '\0')
			{
				if (check_side_char(map, i, j))
					return (1);
			}
			else if (map[i][j] == '0' && (is_in_set(map[i + 1][j], " \0\t")
			|| is_in_set(map[i - 1][j], " \0\t")
			|| is_in_set(map[i][j + 1], " \0\t")
			|| is_in_set(map[i][j - 1], " \0\t")))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	multiple_player(char **map)
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
	if (count != 1)
		return (1);
	return (0);
}
