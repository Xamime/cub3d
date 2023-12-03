/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:47:41 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/03 16:02:56 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	test_tex_paths(char *tex_paths[4])
{
	int	i;
	int	fd;

	// soit ameliorer la fonction soit la degager
	i = 0;
	while (i < 4)
	{
		if (ft_strlen(tex_paths[i]) < 4
			|| ft_strcmp(&tex_paths[i][ft_strlen(tex_paths[i]) - 4], ".png"))
		{
			printf("Error\n%s: wrong texture extension\n", tex_paths[i]);
			return (1);
		}
		fd = open(tex_paths[i], O_RDONLY);
		if (fd == -1)
		{
			printf("Error\n");
			perror(tex_paths[i]);
			return (1);
		}
		else
			close(fd);
		i++;
	}
	return (0);
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

char	*get_textures(int fd, char *tex_paths[4], t_bgrd *bgrd, char **to_split)
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
