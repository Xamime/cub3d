/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:40:16 by xamime            #+#    #+#             */
/*   Updated: 2023/12/03 19:45:47 by jfarkas          ###   ########.fr       */
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

char	*get_file_as_line(t_vars *vars, const char *path,
	t_bg *bg, char *tex_paths[4])
{
	int		fd;
	char	*tmp;
	char	*to_split;

	to_split = NULL;
	fd = open_file(path);
	tmp = get_textures(fd, tex_paths, bg, &to_split);
	remove_endl(tmp);
	if (!is_map(tmp) || check_count(tex_paths, bg) /* || check_id(tmp) >= 0*/)
	{
		if (tmp)
		{
			// if (check_id(tmp) >= 0)
			// 	printf("Error\n%s: Already set\n", tmp);
			// else
			// 	printf("Error\n%s: Bad identifier\n", tmp);
			free(tmp);
		}
		if (check_count(tex_paths, bg))
			printf("Error\nA texture or background color is missing\n");
		else
			printf("Error\nInvalid texture or background\n");
		close(fd);
		return (to_split);
	}
	to_split = get_map(fd, tmp);
	close(fd);
	if (!to_split)
		printf("Error\nInvalid map\n");
	return (to_split);
}

void	init_vars(char *tex_paths[4], t_bg *bg)
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

int	parse_file(t_vars *vars, const char *path, t_bg *bg)
{
	char	*to_split;
	char	*tex_paths[4];

	init_vars(tex_paths, bg);
	to_split = get_file_as_line(vars, path, bg, tex_paths);
	if (!to_split || test_tex_paths(tex_paths))
	{
		free(to_split);
		for (int i = 0; i < 4; i++)
			free(tex_paths[i]);
		return (1);
	}
	to_split[ft_strlen(to_split) - 1] = '\0';
	vars->map = ft_split(to_split, ',');
	free(to_split);
	if (!vars->map)
		return (1);
	if (check_if_map_is_close(vars->map) || multiple_player(vars->map))
	{
		free_2d_array(vars->map);
		for (int i = 0; i < 4; i++)
			free(tex_paths[i]);
		printf("Error\nInvalid map\n");
		return (1);
	}
	vars->mlx = mlx_init(WIDTH, HEIGHT, "cub", true);
	alloc_buffer(vars);
	if (load_textures(vars, tex_paths))
		return (1);
	return (0);
}
