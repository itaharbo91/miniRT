/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:45:16 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 19:17:06 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoi(const char *nptr)
{
	int			i;
	long long	neg;
	long long	num;

	neg = 1;
	num = 0;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return (neg * num);
}
