/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:00:30 by mdesrose          #+#    #+#             */
/*   Updated: 2023/12/07 15:25:28 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	replace_address(char **addr1, char *addr2)
{
	char	*tmp;

	tmp = *addr1;
	*addr1 = addr2;
	free(tmp);
}

void	remove_endl(char *str)
{
	if (str && ft_strlen(str))
		if (str[ft_strlen(str) - 1] == '\n')
			str[ft_strlen(str) - 1] = '\0';
}

int	set_texture(int id, char **tmp, char *str, char *tex_paths[4])
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
