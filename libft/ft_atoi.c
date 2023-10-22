/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:53:28 by mdesrose          #+#    #+#             */
/*   Updated: 2023/10/22 03:56:53 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>

int	ft_atoi(const char *nptr)
{
	int			i;
	long long	nbr;
	int			neg;

	i = 0;
	nbr = 0;
	neg = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (nbr * neg <= -2147483648)
			return (0);
		if (nbr * neg >= 2147483647)
			return (-1);
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	return (nbr * neg);
}

long long	ft_atoll(const char *nptr)
{
	int			i;
	long long	nbr;
	int			neg;

	i = 0;
	nbr = 0;
	neg = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	return (nbr * neg);
}


// Function to convert a float to a string
void floatToChar(float number, char* str, int precision)
{
	int	integerPart;
	int	intLength;
	int	temp;
	int	i;
	float decimalPart;

    if (number < 0)
	{
        *str++ = '-';
        number = -number;
    }
    integerPart = (int)number;
    intLength = 0;
    temp = integerPart;
    while (temp > 0)
	{
        temp /= 10;
        intLength++;
    }
    intLength = (intLength == 0) ? 1 : intLength;
    temp = integerPart;
    i = 1;
    while (i <= intLength)
	{
        str[intLength - i] = '0' + (temp % 10);
        temp /= 10;
        i++;
    }
    if (precision > 0)
	{
        str[intLength] = '.';
        intLength++;
    }
    decimalPart = number - (float)integerPart;
    i = 1;
    while (i <= precision) {
        decimalPart *= 10;
        str[intLength] = '0' + (int)decimalPart;
        decimalPart -= (int)decimalPart;
        intLength++;
        i++;
    }
    str[intLength] = '\0';
}
