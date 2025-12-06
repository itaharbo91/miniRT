/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_calculations_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:56:05 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 19:25:41 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

t_vector	point_to_vector(t_point p)
{
	t_vector	v;

	v.vect_x = p.x;
	v.vect_y = p.y;
	v.vect_z = p.z;
	return (v);
}

t_vector	vector_calculate(t_point a, t_point b)
{
	t_vector	ab;

	ab.vect_x = b.x - a.x;
	ab.vect_y = b.y - a.y;
	ab.vect_z = b.z - a.z;
	return (ab);
}

t_vector	vector_addition(t_vector a, t_vector b)
{
	t_vector	c;

	c.vect_x = a.vect_x + b.vect_x;
	c.vect_y = a.vect_y + b.vect_y;
	c.vect_z = a.vect_z + b.vect_z;
	return (c);
}

t_vector	vector_subtraction(t_vector a, t_vector b)
{
	t_vector	c;

	c.vect_x = a.vect_x - b.vect_x;
	c.vect_y = a.vect_y - b.vect_y;
	c.vect_z = a.vect_z - b.vect_z;
	return (c);
}

t_vector	vector_division(t_vector a, t_vector b)
{
	t_vector	c;

	c.vect_x = a.vect_x / b.vect_x;
	c.vect_y = a.vect_y / b.vect_y;
	c.vect_z = a.vect_z / b.vect_z;
	return (c);
}
