/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_equations_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:19:04 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/28 22:05:32 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "math.h"

t_vector	cap_normal_vector(t_ray *ray, t_cylinder *cylinder, t_vector cap)
{
	t_vector	axis;
	t_vector	normal;

	(void)ray;
	axis = vectors_unit(cylinder->vectors);
	normal = vector_subtraction(cap, point_to_vector(cylinder->points));
	if (vector_dot_product(normal, axis) > EPSILON)
		return (axis);
	return (scalars_mult_by_vectors(-1.0f, axis));
}

int	check_cylinder_height(t_vector point, t_vector center,
		t_vector axis, float height)
{
	t_vector	point_to_center;
	float		projection;
	float		half_height;

	point_to_center = vector_subtraction(point, center);
	projection = vector_dot_product(point_to_center, axis);
	half_height = height / 2.0f;
	if (fabs(projection) > half_height)
		return (0);
	return (1);
}

t_vector	cy_surf_normal_vector(t_vector point, t_vector center,
		t_vector axis)
{
	t_vector	pc;
	t_vector	proj;
	t_vector	normal;
	float		proj_len;

	pc = vector_subtraction(point, center);
	proj_len = vector_dot_product(pc, axis);
	proj = scalars_mult_by_vectors(proj_len, axis);
	normal = vector_subtraction(pc, proj);
	if (vector_magnitude(normal) < EPSILON)
	{
		normal.vect_x = 0.0f;
		normal.vect_y = 1.0f;
		normal.vect_z = 0.0f;
		return (normal);
	}
	return (vectors_unit(normal));
}
