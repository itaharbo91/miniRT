/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersections_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:45:28 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/28 21:42:27 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

static void	cylinder_fill(t_ray *ray, t_cylinder *cylinder, float u)
{
	t_vector	center;
	t_vector	point;
	t_vector	axis;

	if (u <= EPSILON)
		return ;
	center = point_to_vector(cylinder->points);
	point = sp_param_ray_equa(ray->origin, u, ray->direction);
	axis = vectors_unit(cylinder->vectors);
	if (!check_cylinder_height(point, center, axis, cylinder->height))
		return ;
	ray->intersections[ray->intersection_count].object = cylinder;
	ray->intersections[ray->intersection_count].type = CYLINDER;
	ray->intersections[ray->intersection_count].u = u;
	ray->intersections[ray->intersection_count].point = point;
	ray->intersections[ray->intersection_count].normal
		= cy_surf_normal_vector(point, center, axis);
	ray->intersections[ray->intersection_count].distance2
		= u * u * vector_dot_product(ray->direction, ray->direction);
	ray->intersections[ray->intersection_count].color = cylinder->colors;
	ray->intersections[ray->intersection_count].specular = cylinder->specular;
	ray->intersection_count++;
}

static void	process_cylinder_intersections(t_ray *ray, t_cylinder *cylinder,
		t_vector axis, float r2)
{
	t_vector	cross1;
	t_vector	cross2;
	float		b;
	float		delta;
	float		u;

	cross1 = vector_cross_products(ray->direction, axis);
	cross2 = vector_cross_products(vector_subtraction(
				ray->origin, point_to_vector(cylinder->points)), axis);
	if (fabs(vector_dot_product(cross1, cross1)) < EPSILON)
		return ;
	b = 2.0f * vector_dot_product(cross1, cross2);
	delta = b * b - 4 * vector_dot_product(cross1, cross1)
		* (vector_dot_product(cross2, cross2) - r2);
	if (delta < 0.0f)
		return ;
	delta = sqrtf(delta);
	u = (-b - delta) / (2.0f * vector_dot_product(cross1, cross1));
	cylinder_fill(ray, cylinder, u);
	u = (-b + delta) / (2.0f * vector_dot_product(cross1, cross1));
	cylinder_fill(ray, cylinder, u);
}

static void	cylinder_cap_fill(t_ray *ray, t_cylinder *cylinder,
		t_vector cap, float u)
{
	t_vector	point;
	t_vector	to_point;
	float		radius;
	float		distance_sq;
	t_vector	normal;

	normal = cap_normal_vector(ray, cylinder, cap);
	if (u <= EPSILON)
		return ;
	point = sp_param_ray_equa(ray->origin, u, ray->direction);
	to_point = vector_subtraction(point, cap);
	radius = cylinder->diameter / 2.0f;
	distance_sq = vector_dot_product(to_point, to_point);
	if (distance_sq > radius * radius)
		return ;
	ray->intersections[ray->intersection_count].object = cylinder;
	ray->intersections[ray->intersection_count].type = CYLINDER;
	ray->intersections[ray->intersection_count].u = u;
	ray->intersections[ray->intersection_count].point = point;
	ray->intersections[ray->intersection_count].normal = normal;
	ray->intersections[ray->intersection_count].distance2
		= u * u * vector_dot_product(ray->direction, ray->direction);
	ray->intersections[ray->intersection_count].color = cylinder->colors;
	ray->intersections[ray->intersection_count].specular = cylinder->specular;
	ray->intersection_count++;
}

static void	process_cylinder_cap(t_ray *ray, t_cylinder *cylinder)
{
	t_vector	axis;
	t_vector	cap_top;
	t_vector	cap_bottom;
	float		denom;

	axis = vectors_unit(cylinder->vectors);
	cap_top = vector_addition(point_to_vector(cylinder->points),
			scalars_mult_by_vectors((cylinder->height / 2.0f), axis));
	cap_bottom = vector_subtraction(point_to_vector(cylinder->points),
			scalars_mult_by_vectors((cylinder->height / 2.0f), axis));
	denom = vector_dot_product(ray->direction, axis);
	if (fabs(denom) > EPSILON)
		cylinder_cap_fill(ray, cylinder, cap_top,
			(vector_dot_product(vector_subtraction(cap_top, ray->origin),
					axis) / denom));
	if (fabs(denom) > EPSILON)
		cylinder_cap_fill(ray, cylinder, cap_bottom,
			(vector_dot_product(vector_subtraction(cap_bottom, ray->origin),
					axis) / denom));
}

void	cylinder_intersections(t_minirt *mini, t_ray *ray)
{
	t_vector	axis;
	float		r2;
	t_cylinder	*cylinder;
	int			i;

	i = 0;
	while (i < mini->scene.cylinder_count)
	{
		cylinder = &mini->scene.cylinders[i];
		axis = vectors_unit(cylinder->vectors);
		r2 = cylinder->diameter / 2.0f;
		r2 *= r2;
		process_cylinder_intersections(ray, cylinder, axis, r2);
		process_cylinder_cap(ray, cylinder);
		i++;
	}
}
