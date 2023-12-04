/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:00:30 by mdesrose          #+#    #+#             */
/*   Updated: 2023/12/04 03:54:26 by jfarkas          ###   ########.fr       */
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
