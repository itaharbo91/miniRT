/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:06:20 by itaharbo          #+#    #+#             */
/*   Updated: 2025/09/13 17:11:10 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

static t_color	apply_checkerboard_plane(t_vector point, t_plane *plane)
{
	t_vector	relative;
	t_vector	n;
	t_vector	ref;
	t_vector	u_axis;
	t_vector	v_axis;

	relative.vect_x = point.vect_x - plane->points.x;
	relative.vect_y = point.vect_y - plane->points.y;
	relative.vect_z = point.vect_z - plane->points.z;
	n = vectors_unit(plane->vectors);
	if (fabsf(n.vect_x) <= fabsf(n.vect_y) && fabsf(n.vect_x)
		<= fabsf(n.vect_z))
		ref = (t_vector){1, 0, 0};
	else if (fabsf(n.vect_y) <= fabsf(n.vect_x) && fabsf(n.vect_y)
		<= fabsf(n.vect_z))
		ref = (t_vector){0, 1, 0};
	else
		ref = (t_vector){0, 0, 1};
	u_axis = vectors_unit(vector_cross_products(ref, n));
	v_axis = vectors_unit(vector_cross_products(n, u_axis));
	if ((((int)floorf(vector_dot_product(relative, u_axis) / 1.0f)
				+ (int)floorf(vector_dot_product(relative, v_axis) / 1.0f))
			& 1) == 1)
		return ((t_color){255, 255, 255});
	return ((t_color){0, 0, 0});
}

static t_color	apply_checkerboard_sphere(t_vector point, t_sphere *sphere)
{
	t_vector	relative_point;
	float		u;
	float		v;
	int			pattern;

	relative_point.vect_x = point.vect_x - sphere->points.x;
	relative_point.vect_y = point.vect_y - sphere->points.y;
	relative_point.vect_z = point.vect_z - sphere->points.z;
	relative_point.vect_x /= sphere->diameter / 2.0f;
	relative_point.vect_y /= sphere->diameter / 2.0f;
	relative_point.vect_z /= sphere->diameter / 2.0f;
	u = (atan2f(relative_point.vect_z, relative_point.vect_x) + M_PI)
		/ (2.0f * M_PI);
	v = acosf(fmaxf(-1.0f, fminf(1.0f, relative_point.vect_y)))
		/ M_PI;
	pattern = ((int)(u * 20.0f) + (int)(v * 10.0f)) % 2;
	if (pattern == 0)
		return ((t_color){0, 0, 0});
	return ((t_color){255, 255, 255});
}

static t_color	apply_checkerboard_cylinder(t_vector p, t_cylinder *cyl)
{
	t_vector	axis;
	t_vector	rel;
	t_vector	ref;
	t_vector	u_axis;
	t_vector	v_axis;

	axis = vectors_unit(cyl->vectors);
	rel = vector_subtraction(p, point_to_vector(cyl->points));
	if (fabsf(axis.vect_x) < 0.9f)
		ref = ((t_vector){1, 0, 0});
	else
		ref = ((t_vector){0, 1, 0});
	u_axis = vectors_unit(vector_cross_products(axis, ref));
	v_axis = vectors_unit(vector_cross_products(axis, u_axis));
	if (fabsf(vector_dot_product(rel, axis)) >= (cyl->height * 0.5f) - 1e-4)
		return (cylinder_checkerboard_cap(vector_dot_product(rel, axis),
				axis, rel, cyl->diameter * 0.5f));
	return (cylinder_checkerboard_around(cyl, rel, u_axis, v_axis));
}

static t_color	apply_checkerboard_cone(t_vector point, t_cone *cone)
{
	t_vector	axis;
	t_vector	rel_point;
	float		height;
	t_vector	axis_proj;
	t_vector	ref;

	axis = vectors_unit(cone->vectors);
	rel_point = vector_subtraction(point, point_to_vector(cone->points));
	height = vector_dot_product(rel_point, axis);
	axis_proj = scalars_mult_by_vectors(height, axis);
	if (fabsf(axis.vect_x) < 0.9f)
		ref = ((t_vector){1, 0, 0});
	else
		ref = ((t_vector){0, 1, 0});
	if (fabsf(height - cone->height) < BIAS)
		return (cone_checkerboard_cap(cone,
				vector_subtraction(rel_point, axis_proj), axis, ref));
	return (cone_checkerboard_around(cone,
			vector_subtraction(rel_point, axis_proj), height, ref));
}

t_color	get_object_color(t_intersection *intersection)
{
	t_color	color;

	color = intersection->color;
	if (intersection->type == SPHERE
		&& ((t_sphere *)intersection->object)->checkerboard == true)
		color = apply_checkerboard_sphere(intersection->point,
				(t_sphere *)intersection->object);
	else if (intersection->type == PLANE
		&& ((t_plane *)intersection->object)->checkerboard == true)
		color = apply_checkerboard_plane(intersection->point,
				(t_plane *)intersection->object);
	else if (intersection->type == CYLINDER
		&& ((t_cylinder *)intersection->object)->checkerboard == true)
		color = apply_checkerboard_cylinder(intersection->point,
				(t_cylinder *)intersection->object);
	else if (intersection->type == CONE
		&& ((t_cone *)intersection->object)->checkerboard == true)
		color = apply_checkerboard_cone(intersection->point,
				(t_cone *)intersection->object);
	return (color);
}
