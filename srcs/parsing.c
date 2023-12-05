/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:40:16 by xamime            #+#    #+#             */
/*   Updated: 2023/12/05 14:11:28 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	open_file(const char *path)
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

static char	*get_file_as_line(const char *path,
	t_bg *bg, char *tex_paths[4])
{
	int		fd;
	char	*tmp;
	char	*file_as_line;

	file_as_line = NULL;
	fd = open_file(path);
	tmp = get_textures(fd, tex_paths, bg);
	remove_endl(tmp);
	if (!is_map(tmp) || check_count(tex_paths, bg))
	{
		free(tmp);
		close(fd);
		return (file_as_line);
	}
	file_as_line = get_map(fd, tmp);
	close(fd);
	if (!file_as_line)
		printf("Error\nInvalid map\n");
	return (file_as_line);
}

static void	init_parsing_vars(char *tex_paths[4], t_bg *bg)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		tex_paths[i] = NULL;
		i++;
	}
	bg->color_set = 0;
}

static int	check_map(t_vars *vars, char *tex_paths[4])
{
	if (!vars->map)
		return (1);
	if (check_if_map_is_close(vars->map) || multiple_player(vars->map))
	{
		free_2d_array(vars->map);
		free_tex_paths(tex_paths);
		printf("Error\nInvalid map\n");
		return (1);
	}
	return (0);
}

int	parse_file(t_vars *vars, const char *path, t_bg *bg)
{
	char	*to_split;
	char	*tex_paths[4];

	init_parsing_vars(tex_paths, bg);
	to_split = get_file_as_line(path, bg, tex_paths);
	if (!to_split || test_tex_paths(tex_paths))
	{
		free(to_split);
		free_tex_paths(tex_paths);
		return (1);
	}
	to_split[ft_strlen(to_split) - 1] = '\0';
	vars->map = ft_split(to_split, ',');
	free(to_split);
	if (check_map(vars, tex_paths))
		return (1);
	vars->mlx = mlx_init(WIDTH, HEIGHT, "cub", 1);
	alloc_buffer(vars);
	if (!vars->buffer || load_textures(vars, tex_paths))
		return (1);
	return (0);
}
