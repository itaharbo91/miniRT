/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_calc_bis_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:54:34 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 19:25:37 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

t_vector	scalars_mult_by_vectors(float u, t_vector a)
{
	t_vector	ua;

	ua.vect_x = u * a.vect_x;
	ua.vect_y = u * a.vect_y;
	ua.vect_z = u * a.vect_z;
	return (ua);
}

float	vector_magnitude(t_vector a)
{
	return (sqrtf(a.vect_x * a.vect_x + a.vect_y
			* a.vect_y + a.vect_z * a.vect_z));
}

t_vector	vectors_unit(t_vector a)
{
	float		magnitude;
	t_vector	v;

	v.vect_x = 0;
	v.vect_y = 0;
	v.vect_z = 0;
	magnitude = vector_magnitude(a);
	if (magnitude > EPSILON)
	{
		v.vect_x = a.vect_x / magnitude;
		v.vect_y = a.vect_y / magnitude;
		v.vect_z = a.vect_z / magnitude;
	}
	return (v);
}

float	vector_dot_product(t_vector a, t_vector b)
{
	return (a.vect_x * b.vect_x + a.vect_y * b.vect_y + a.vect_z * b.vect_z);
}

t_vector	vector_cross_products(t_vector a, t_vector b)
{
	t_vector	c;

	c.vect_x = a.vect_y * b.vect_z - a.vect_z * b.vect_y;
	c.vect_y = a.vect_z * b.vect_x - a.vect_x * b.vect_z;
	c.vect_z = a.vect_x * b.vect_y - a.vect_y * b.vect_x;
	return (c);
}
