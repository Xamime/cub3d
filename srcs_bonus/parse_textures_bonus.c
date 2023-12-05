/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:47:41 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/05 20:19:01 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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

static char	*gnl_non_empty(int fd)
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

static int	set_texture(int id, char **tmp, char *str, char *tex_paths[4])
{
	if (id >= 0 && id < 4 && tex_paths[id])
	{
		printf("Error\n%s: texture already set\n", tmp[0]);
		free_2d_array(tmp);
		free(str);
		return (-1);
	}
	tex_paths[id] = ft_strdup(tmp[1]);
	tex_paths[id][ft_strlen(tex_paths[id]) - 1] = 0;
	return (0);
}

static int	set_tmp(char ***tmp, char *str)
{
	*tmp = ft_split(str, ' ');
	if (!(*tmp) || !(*tmp)[0] || ((*tmp)[1] && (*tmp)[2]))
	{
		if (!(*tmp))
			printf("Error\nMap is empty\n");
		free_2d_array(*tmp);
		return (-1);
	}
	return (0);
}

char	*get_textures(int fd, char *tex_paths[4], t_bg *bg)
{
	char	*str;
	char	**tmp;
	int		id;

	id = 0;
	str = "";
	while (str && id != -1)
	{
		str = gnl_non_empty(fd);
		if (set_tmp(&tmp, str) == -1)
			break;
		id = check_id(tmp[0]);
		if (id != -1 && id != FLOOR && id != CEILING)
		{
			if (set_texture(id, tmp, str, tex_paths) == -1)
				return (NULL);
		}
		else if (id != -1)
			id = get_background(bg, tmp[1], id);
		free_2d_array(tmp);
		if (id != -1)
			free(str);
	}
	return (str);
}
