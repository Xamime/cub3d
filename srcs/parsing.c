/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:40:16 by xamime            #+#    #+#             */
/*   Updated: 2023/12/02 15:00:24 by jfarkas          ###   ########.fr       */
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

static int	check_id(char *str)
{
	if (!ft_strcmp(str, "SO"))
		return (SOUTH);
	else if (!ft_strcmp(str, "NO"))
		return (NORTH);
	else if (!ft_strcmp(str, "EA"))
		return (EAST);
	else if (!ft_strcmp(str, "WE"))
		return (WEST);
	else if (!ft_strcmp(str, "F"))
		return (FLOOR);
	else if (!ft_strcmp(str, "C"))
		return (CEILING);
	return (-1);
}

int	is_empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '\n')
		return (1);
	return (0);
}

char	*gnl_non_empty(int fd)
{
	char	*str;

	str = get_next_line(fd);
	while (str && is_empty_line(str))
	{
		free(str);
		str = get_next_line(fd);
	}
	return (str);
}

char	*parse_textures(int fd, char *tex_paths[4], t_bgrd *bgrd, char **to_split)
{
	char	*str;
	char	**tmp;
	int		id;

	id = 0;
	str = "";
	while (str && id != -1)
	{
		str = gnl_non_empty(fd);
		tmp = ft_split(str, ' ');
		if (!tmp || !tmp[0] || (tmp[1] && tmp[2]))
		{
			free_2d_array(tmp);
			break ;
		}
		id = check_id(tmp[0]);
		if (id >= 0 && id < 4 && tex_paths[id])
		{
			printf("Error\n%s: texture already set\n", tmp[0]);
			free_2d_array(tmp);
			free(str);
			return (NULL);
		}
		if (id != -1 && id != FLOOR && id != CEILING)
		{
			tex_paths[id] = ft_strdup(tmp[1]);
			tex_paths[id][ft_strlen(tex_paths[id]) - 1] = 0;
		}
		else if (id != -1)
			init_background(bgrd, tmp[1], id);
		free_2d_array(tmp);
		if (id != -1)
			free(str);
	}
	return (str);
}

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
	while (str)
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
	return (map);
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
	tmp = parse_textures(fd, tex_paths, bgrd, &to_split);
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
