/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:40:16 by xamime            #+#    #+#             */
/*   Updated: 2023/10/31 15:34:34 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_in_set(char c, char *charset)
{
    int i;

    i = 0;
    while (charset[i])
    {
        if (c == charset[i])
            return (1);
        i++;
    }
    return (0);
}

int	check_side_char(char **map, int i, int j)
{
	if (map[i][j] == '0' && (j == 0 || i == 0 || !map[i + 1] || !map[i][j + 1]))
	{
		return (1);
	}
	return (0);
}

// risque de segfault si map[0] est regarder
// espace seulement suivis d'espace ou de 1,
int check_if_map_is_close(char **map)
{
    int i;
    int j;

    i = 0;
    while(map[i])
    {
        j = 0;
        while (map[i][j])
        {
			if (i == 0 || j == 0 || map[i + 1] == NULL || map[i][j + 1] == '\0')
			{
				if (check_side_char(map, i, j))
					return (1);
			}
			else if (map[i][j] == '0' && (is_in_set(map[i + 1][j], " \0\t")
            || is_in_set(map[i - 1][j], " \0\t")
			|| is_in_set(map[i][j + 1], " \0\t")
            || is_in_set(map[i][j - 1], " \0\t")))
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

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

int	check_dir_path(char *str, int i)
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

void	extract_path(t_vars *vars, char *str, int dir, t_bgrd *bgrd)
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

void	read_map(t_vars *vars, char *str, char **to_split)
{
	int		i;
	char	*tmp;
	static	int	count;

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
	//*todo free
}

void	find_path_tex(t_vars *vars, char *str, t_bgrd *bgrd, char **to_split)
{
	int	i;
	int	dir;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\n')
	{
		free(str);
		return ;
	}
	dir = check_dir_path(str, i);
	if (dir == -1)
	{
		printf("Error\nBad identifier\n");
		free(str);
		exit(1);
	}
	else if (dir == MAP)
		read_map(vars, str, to_split);
	else
		extract_path(vars, str + i, dir, bgrd);
	free(str);
}

int	parse_file(t_vars *vars, const char *path, t_bgrd *bgrd)
{
	int		fd;
	char	*tmp;
	char	*to_split;
	int i = 0;

	to_split = "";
	fd = open_file(path);
	while ((tmp = get_next_line(fd)))
	{
		find_path_tex(vars, tmp, bgrd, &to_split); 
		//free(tmp);
	}
	while (to_split[i])
		i++;
	to_split[i-1] = '\0';
	vars->map = ft_split(to_split, ',');
	free(to_split);
	if (check_if_map_is_close(vars->map))
	{
		printf("Error\nInvalid map\n");
		return (1);
	}
	return (0);
}
