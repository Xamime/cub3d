/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamime <xamime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:40:16 by xamime            #+#    #+#             */
/*   Updated: 2023/10/27 14:19:29 by xamime           ###   ########.fr       */
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

// risque de segfault si map[0] est regarder
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
            if (map[i][j] == '0' && (is_in_set(map[i + 1][j], " \n")
            || is_in_set(map[i - 1][j], " \n") || is_in_set(map[i][j + 1], " \n")
            || is_in_set(map[i][j - 1], " \n")))
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}