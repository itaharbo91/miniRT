/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:09:49 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 19:17:42 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static float	strtof_helpers(const char *theString, int *i)
{
	float	res;
	float	fract;
	float	div;

	res = 0.0f;
	fract = 0.0f;
	div = 1.0f;
	while (theString[*i] >= '0' && theString[*i] <= '9')
	{
		res = res * 10.0f + (theString[*i] - '0');
		(*i)++;
	}
	if (theString[*i] == '.')
	{
		(*i)++;
		while (theString[*i] >= '0' && theString[*i] <= '9')
		{
			fract = fract * 10.0f + (theString[*i] - '0');
			div *= 10.0f;
			(*i)++;
		}
		res += fract / div;
	}
	return (res);
}

float	ft_strtof(const char *theString, char **end)
{
	int		i;
	int		sign;
	float	res;

	i = 0;
	sign = 1;
	res = 0.0f;
	if (theString[i] == '-' || theString[i] == '+')
	{
		if (theString[i] == '-')
			sign *= -1;
		i++;
	}
	res = strtof_helpers(theString, &i);
	if (end)
		*end = (char *)&theString[i];
	return (res * sign);
}
