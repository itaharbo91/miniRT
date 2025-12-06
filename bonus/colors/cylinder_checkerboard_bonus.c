/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_checkerboard.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:14:38 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/28 20:01:13 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

static int	cap_pattern(t_vector axis, t_vector ref, t_vector radial_vec,
		float radius)
{
	int			pattern;
	t_vector	u_axis;
	t_vector	v_axis;
	float		u;
	float		v;

	u_axis = vectors_unit(vector_cross_products(axis, ref));
	v_axis = vectors_unit(vector_cross_products(axis, u_axis));
	u = vector_dot_product(radial_vec, u_axis);
	v = vector_dot_product(radial_vec, v_axis);
	pattern = ((int)floorf((u + radius) / (radius / 2.2f))
			+ (int)floorf((v + radius) / (radius / 2.2f))) & 1;
	return (pattern);
}

t_color	cylinder_checkerboard_cap(float h, t_vector axis, t_vector rel,
		float radius)
{
	int			pattern;
	t_vector	axis_proj;
	t_vector	radial_vec;
	t_vector	ref;

	axis_proj = scalars_mult_by_vectors(h, axis);
	radial_vec = vector_subtraction(rel, axis_proj);
	if (fabsf(axis.vect_x) < 0.9f)
		ref = (t_vector){1, 0, 0};
	else
		ref = (t_vector){0, 1, 0};
	pattern = cap_pattern(axis, ref, radial_vec, radius);
	if (pattern == 0)
		return ((t_color){0, 0, 0});
	return ((t_color){255, 255, 255});
}

t_color	cylinder_checkerboard_around(t_cylinder *cyl, t_vector rel,
		t_vector u_axis, t_vector v_axis)
{
	float		u_coord;
	float		v_coord;
	t_vector	proj;
	t_vector	radial;
	float		theta;

	proj = scalars_mult_by_vectors(vector_dot_product(rel,
				vectors_unit(cyl->vectors)), vectors_unit(cyl->vectors));
	radial = vector_subtraction(rel, proj);
	theta = atan2f(vector_dot_product(radial, u_axis),
			vector_dot_product(radial, v_axis));
	if (theta < 0)
		theta += 2.0f * M_PI;
	u_coord = theta / (2.0f * M_PI);
	v_coord = (vector_dot_product(rel, vectors_unit(cyl->vectors))
			+ (cyl->height * 0.5f)) / cyl->height;
	if (((((int)floorf(u_coord * 16)) + ((int)floorf(v_coord * 10))) & 1) == 0)
		return ((t_color){0, 0, 0});
	return ((t_color){255, 255, 255});
}
