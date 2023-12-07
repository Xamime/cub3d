/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:54:36 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/07 17:03:02 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_map(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_strchr("01 NSWE", str[i]))
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

char	*get_map(int fd, char *str)
{
	char	*map;

	map = NULL;
	while (str && !is_empty_line(str))
	{
		remove_endl(str);
		if (!is_map(str))
		{
			free(str);
			free(map);
			map = NULL;
			break ;
		}
		if (map)
			replace_address(&map, ft_strjoin(map, str));
		else
			map = ft_strdup(str);
		replace_address(&map, ft_strjoin(map, ","));
		free(str);
		str = get_next_line(fd);
	}
	if (str)
		free(str);
	return (map);
}
