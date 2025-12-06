/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_checkerboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:59:17 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/28 20:58:41 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

t_color	cone_checkerboard_cap(t_cone *cone, t_vector radial_vec,
		t_vector axis, t_vector ref)
{
	int			pattern;
	float		size;
	t_vector	u_axis;
	t_vector	v_axis;
	float		base_radius;

	u_axis = vectors_unit(vector_cross_products(axis, ref));
	v_axis = vectors_unit(vector_cross_products(axis, u_axis));
	base_radius = cone->diameter * 0.5f;
	size = base_radius / 3.0f;
	pattern = (((int)floorf((vector_dot_product(radial_vec, u_axis)
						+ base_radius) / size)
				+ (int)floorf((vector_dot_product(radial_vec, v_axis)
						+ base_radius) / size)) & 1);
	if (pattern == 0)
		return ((t_color){0, 0, 0});
	return ((t_color){255, 255, 255});
}

t_color	cone_checkerboard_around(t_cone *cone, t_vector radial_vec,
		float height, t_vector ref)
{
	int			pattern;
	float		theta;
	t_vector	u_axis;
	t_vector	v_axis;
	t_vector	axis;

	axis = vectors_unit(cone->vectors);
	u_axis = vectors_unit(vector_cross_products(axis, ref));
	v_axis = vectors_unit(vector_cross_products(axis, u_axis));
	theta = atan2f(vector_dot_product(radial_vec, u_axis),
			vector_dot_product(radial_vec, v_axis));
	if (theta < 0.0f)
		theta += 2.0f * M_PI;
	pattern = (((int)(10 * height / cone->height))
			+ ((int)(16 * theta / (2.0f * M_PI)))) & 1;
	if (pattern == 0)
		return ((t_color){0, 0, 0});
	return ((t_color){255, 255, 255});
}
