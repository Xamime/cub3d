/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:47:41 by jfarkas           #+#    #+#             */
/*   Updated: 2023/12/07 15:38:20 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static int	set_tmp(char ***tmp, char *str)
{
	*tmp = ft_split(str, ' ');
	if (!(*tmp) || !(*tmp)[0] || ((*tmp)[1] && (*tmp)[2]))
	{
		if (!(*tmp))
			printf("Error\nMap is empty\n");
		else if ((*tmp)[0])
			printf("Error\nBad identifier\n");
		free_2d_array(*tmp);
		return (-1);
	}
	return (0);
}

static void	print_if_error(int id, char *str)
{
	if (id == -1)
	{
		remove_endl(str);
		if (!is_map(str))
			printf("Error\nBad identifier\n");
	}
}

char	*get_textures(int fd, char *tex_paths[4], t_bg *bg)
{
	char	*str;
	char	**tmp;
	int		id;

	id = 0;
	str = "";
	while (str && id >= 0)
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
		print_if_error(id, str);
		free_2d_array(tmp);
		if (id >= 0)
			free(str);
	}
	return (str);
}
