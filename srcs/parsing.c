/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:40:16 by xamime            #+#    #+#             */
/*   Updated: 2023/12/03 16:05:04 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	open_file(const char *path)
{
	int	fd;

	if (!path)
	{
		printf("Error\nNo map provided\n");
		exit(1);
	}
	if (ft_strlen(path) < 4 || ft_strcmp(&path[ft_strlen(path) - 4], ".cub"))
	{
		printf("Error\nWrong file format\n");
		exit(1);
	}
	fd = open(path, O_RDONLY, 644);
	if (fd == -1)
	{
		printf("Error\n%s: could not open the map\n", path);
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
	free_2d_array(colors);
}

char	*get_file_as_line(t_vars *vars, const char *path,
	t_bgrd *bgrd, char *tex_paths[4])
{
	int		fd;
	char	*tmp;
	char	*to_split;

	for (int i = 0; i < 4; i++)
		tex_paths[i] = NULL;
	to_split = NULL;
	fd = open_file(path);
	tmp = get_textures(fd, tex_paths, bgrd, &to_split);
	remove_endl(tmp);
	if (!is_map(tmp) || check_id(tmp) >= 0)
	{
		if (tmp)
		{
			if (check_id(tmp) >= 0)
				printf("Error\n%s: Already set\n", tmp);
			else
				printf("Error\n%s: Bad identifier\n", tmp);
			free(tmp);
		}
		close(fd);
		return (to_split);
	}
	to_split = get_map(fd, tmp);
	close(fd);
	if (!to_split)
		printf("Error\nInvalid map\n");
	return (to_split);
}

int	parse_file(t_vars *vars, const char *path, t_bgrd *bgrd)
{
	char	*to_split;
	char	*tex_paths[4];

	to_split = get_file_as_line(vars, path, bgrd, tex_paths);
	if (!to_split /*|| test_tex_paths(tex_paths)*/)
		return (1);
	to_split[ft_strlen(to_split) - 1] = '\0';
	vars->map = ft_split(to_split, ',');
	free(to_split);
	if (!vars->map)
		return (1);
	// for (int i = 0; vars->map[i]; i++)
	// 	printf("map : %s\n", vars->map[i]);
	if (check_if_map_is_close(vars->map) || multiple_player(vars->map))
	{
		printf("Error\nInvalid map\n");
		return (1);
	}
	vars->mlx = mlx_init(WIDTH, HEIGHT, "cub", true);
	alloc_buffer(vars);
	if (load_textures(vars, tex_paths))
		return (1);
	return (0);
}
