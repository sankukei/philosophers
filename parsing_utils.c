/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:07:08 by leothoma          #+#    #+#             */
/*   Updated: 2025/04/08 16:07:12 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	d_atoi(char *str)
{
	int		i;
	int		y;
	double	res1;
	double	res2;
	int		neg;

	neg = 1;
	res1 = 0;
	res2 = 0;
	i = 0;
	y = 0;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (str[i] && str[i] != '.')
		res1 = (res1 * 10) + str[i++] - 48;
	i++;
	while (str[i] && ++y)
		res2 = (res2 * 10) + str[i++] - 48;
	while (y-- > 0)
		res2 /= 10;
	return ((res1 + res2) * neg);
}

size_t	ft_atoi(const char *str)
{
	int			i;
	size_t		res;
	int			count;
	int			neg;

	i = 0;
	res = 0;
	count = 0;
	neg = 0;
	while (((str[i] >= 9 && str[i] <= 13) || (str[i]) == 32))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		count++;
		if (str[i] == '-')
			neg++;
		if (count > 1)
			return (0);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + str[i++] - 48;
	if (neg % 2 == 1)
		res *= -1;
	return (res);
}
