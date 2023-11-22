/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:40:16 by xamime            #+#    #+#             */
/*   Updated: 2023/11/22 17:53:13 by mdesrose         ###   ########.fr       */
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

char	*get_file_as_line(t_vars *vars, const char *path, t_bgrd *bgrd)
{
	int		fd;
	char	*tmp;
	char	*to_split;

	to_split = "";
	fd = open_file(path);
	tmp = get_next_line(fd);
	while (tmp)
	{
		if (-1 == find_path_tex(vars, tmp, bgrd, &to_split))
		{
			close(fd);
			return (NULL);
		}
		tmp = get_next_line(fd);
	}
	close(fd);
	return (to_split);
}

int	parse_file(t_vars *vars, const char *path, t_bgrd *bgrd)
{
	char	*to_split;

	to_split = get_file_as_line(vars, path, bgrd);
	if (!to_split)
		return (1);
	to_split[ft_strlen(to_split) - 1] = '\0';
	vars->map = ft_split(to_split, ',');
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
