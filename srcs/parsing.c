/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:40:16 by xamime            #+#    #+#             */
/*   Updated: 2023/11/20 15:23:10 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	open_file(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY, 644);
	if (fd == -1)
	{
		printf("Error\n%s : %s\n", path, strerror(errno));
		exit(1);
	}
	return (fd);
}

void	init_background(t_bgrd *bgrd, char *str, int dir)
{
	char	**colors;
	int		i;

	i = 0;
	colors = ft_split(str, ',');
	if (dir == FLOOR)
	{
		bgrd->floor.r = ft_atoi(colors[0]);
		bgrd->floor.g = ft_atoi(colors[1]);
		bgrd->floor.b = ft_atoi(colors[2]);
	}
	else
	{
		bgrd->ceil.r = ft_atoi(colors[0]);
		bgrd->ceil.g = ft_atoi(colors[1]);
		bgrd->ceil.b = ft_atoi(colors[2]);
	}
	while (colors[i])
	{
		free(colors[i]);
		i++;
	}
	free(colors);
}

char	**malloc_map(char **split)
{
	char	**map;
	int			lines_nb;
	int			line;

	lines_nb = 0;
	while (split[lines_nb])
		lines_nb++;
	map = malloc(sizeof(char *) * lines_nb + 1);
	if (!map)
		return (NULL);
	map[lines_nb] = NULL;
	line = 0;
	while (split[line])
	{
		map[line] = malloc(sizeof(char) * (ft_strlen(split[line]) + 1));
		if (!map[line])
			return (NULL);
		map[line][ft_strlen(split[line])] = 0;
		line++;
	}
	return (map);
}

char	**char_to_obj_map(char **split)
{
	char	**map;
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
			map[y][x] = split[y][x];
			x++;
		}
		y++;
	}
	free_2d_array(split);
	return (map);
}

int	parse_file(t_vars *vars, const char *path, t_bgrd *bgrd)
{
	// close le fd
	int		fd;
	char	*tmp;
	char	*to_split;
	int i = 0;

	to_split = "";
	fd = open_file(path);
	while ((tmp = get_next_line(fd)))
		find_path_tex(vars, tmp, bgrd, &to_split);
	while (to_split[i])
		i++;
	to_split[i-1] = '\0';
	vars->map = char_to_obj_map(ft_split(to_split, ','));
	free(to_split);
	if (!vars->map)
		return (1);
	if (check_if_map_is_close(vars->map) || multiple_player(vars->map))
	{
		printf("Error\nInvalid map\n");
		return (1);
	}
	return (0);
}
