/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:20:08 by maxime            #+#    #+#             */
/*   Updated: 2023/11/22 18:33:55 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	extract_path(t_vars *vars, char *str, int dir, t_bgrd *bgrd)
{
	int	i;

	i = 0;
	if (dir == FLOOR || dir == CEILING)
		i++;
	else
		i += 2;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\n')
		return ;
	if (dir != FLOOR && dir != CEILING)
		init_textures_test(vars, str + i, dir);
	else
		init_background(bgrd, str + i, dir);
}

static int	check_dir_path(char *str, int i)
{
	if (str[i] == 'S' && str[i + 1] == 'O')
		return (SOUTH);
	else if (str[i] == 'N' && str[i + 1] == 'O')
		return (NORTH);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		return (EAST);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		return (WEST);
	else if (str[i] == 'F')
		return (FLOOR);
	else if (str[i] == 'C')
		return (CEILING);
	else if (str[i] == '1' || str[i] == '0')
		return (MAP);
	return (-1);
}

static void	read_map(t_vars *vars, char *str, char **to_split)
{
	int			i;
	char		*tmp;
	static int	count;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	str[i] = '\0';
	tmp = ft_strjoin(*to_split, str);
	if (count > 0)
		free(*to_split);
	*to_split = ft_strjoin(tmp, ",");
	free(tmp);
	count++;
}

int	find_path_tex(t_vars *vars, char *str, t_bgrd *bgrd, char **to_split)
{
	int	i;
	int	dir;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\n')
	{
		free(str);
		return (0);
	}
	dir = check_dir_path(str, i);
	if (dir == -1)
	{
		printf("Error\nBad identifier\n");
		free(str);
		return (-1);
	}
	else if (dir == MAP)
		read_map(vars, str, to_split);
	else
		extract_path(vars, str + i, dir, bgrd);
	free(str);
	return (0);
}
