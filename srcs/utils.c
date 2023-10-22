/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 07:07:48 by jfarkas           #+#    #+#             */
/*   Updated: 2023/10/22 07:09:49 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

// Function to convert a float to a string
void	float_to_char(float number, char* str, int precision)
{
	int		integerPart;
	int		intLength;
	int		temp;
	int		i;
	float	decimalPart;

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
