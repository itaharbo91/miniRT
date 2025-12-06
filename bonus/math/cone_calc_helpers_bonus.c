/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_calc_helpers_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:24:08 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/29 14:25:01 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

bool	check_cone_height(t_vector point, t_cone *cone)
{
	t_vector	apex;
	t_vector	axis;
	float		height_proj;

	apex = point_to_vector(cone->points);
	axis = vectors_unit(cone->vectors);
	height_proj = vector_dot_product(vector_subtraction(point, apex), axis);
	if (height_proj < 0.001f)
		return (false);
	if (height_proj >= 0 && height_proj <= cone->height)
		return (true);
	return (false);
}

float	vector_length(t_vector v)
{
	return (sqrtf(v.vect_x * v.vect_x + v.vect_y * v.vect_y
			+ v.vect_z * v.vect_z));
}

t_vector	cone_normal_vector(t_vector point, t_cone *cone)
{
	t_vector	axis;
	t_vector	v;
	float		m;
	float		k;
	t_vector	n;

	axis = vectors_unit(cone->vectors);
	v = vector_subtraction(point, point_to_vector(cone->points));
	m = vector_dot_product(v, axis);
	k = (cone->diameter / 2.0f) / cone->height;
	n = vector_subtraction(v, scalars_mult_by_vectors((1 + k * k) * m, axis));
	return (vectors_unit(n));
}
