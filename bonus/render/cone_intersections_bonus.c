/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersections_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:14:15 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/29 14:33:42 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

void	cone_fill(t_ray *ray, t_cone *cone, float u)
{
	t_vector	apex;
	t_vector	point;

	if (u <= EPSILON)
		return ;
	apex = point_to_vector(cone->points);
	point = sp_param_ray_equa(ray->origin, u, ray->direction);
	if (!check_cone_height(point, cone))
		return ;
	ray->intersections[ray->intersection_count].object = cone;
	ray->intersections[ray->intersection_count].type = CONE;
	ray->intersections[ray->intersection_count].u = u;
	ray->intersections[ray->intersection_count].point = point;
	ray->intersections[ray->intersection_count].normal
		= cone_normal_vector(point, cone);
	ray->intersections[ray->intersection_count].distance2
		= u * u * vector_dot_product(ray->direction, ray->direction);
	ray->intersections[ray->intersection_count].color = cone->colors;
	ray->intersections[ray->intersection_count].specular = cone->specular;
	ray->intersection_count++;
}

static void	process_cone_intersections(t_ray *ray, t_cone *cone)
{
	float	a;
	float	b;
	float	c;
	float	t1;
	float	t2;

	a = a_discriminant(ray, cone);
	b = b_discriminant(ray, cone);
	c = c_discriminant(ray, cone);
	if ((b * b - 4.0f * a * c) < 0)
		return ;
	t1 = (-b - sqrtf(b * b - 4.0f * a * c)) / (2.0f * a);
	t2 = (-b + sqrtf(b * b - 4.0f * a * c)) / (2.0f * a);
	if (t1 > EPSILON)
		t_choose_fill(ray, cone, t1);
	if (t2 > EPSILON)
		t_choose_fill(ray, cone, t2);
}

static void	cone_cap_fill(t_ray *ray, t_cone *cone, float t, t_vector p)
{
	ray->intersections[ray->intersection_count].object = cone;
	ray->intersections[ray->intersection_count].type = CONE;
	ray->intersections[ray->intersection_count].u = t;
	ray->intersections[ray->intersection_count].point = p;
	ray->intersections[ray->intersection_count].normal = vectors_unit(
			cone->vectors);
	ray->intersections[ray->intersection_count].distance2 = t * t
		* vector_dot_product(ray->direction, ray->direction);
	ray->intersections[ray->intersection_count].color = cone->colors;
	ray->intersections[ray->intersection_count].specular = cone->specular;
	ray->intersection_count++;
}

static void	process_cone_cap(t_ray *ray, t_cone *cone)
{
	float		t;
	t_vector	p;
	t_vector	axis;
	t_vector	base_center;
	float		dist;

	axis = vectors_unit(cone->vectors);
	base_center = vector_addition(point_to_vector(cone->points),
			scalars_mult_by_vectors(cone->height, axis));
	if (fabsf(vector_dot_product(ray->direction, axis)) < EPSILON)
		return ;
	t = vector_dot_product(vector_subtraction(base_center, ray->origin), axis)
		/ vector_dot_product(ray->direction, axis);
	if (t < EPSILON)
		return ;
	p = vector_addition(ray->origin, scalars_mult_by_vectors(t,
				ray->direction));
	dist = vector_length(vector_subtraction(p, base_center));
	if (dist > cone->diameter / 2.0f)
		return ;
	cone_cap_fill(ray, cone, t, p);
}

void	cone_intersections(t_minirt *mini, t_ray *ray)
{
	t_vector	axis;
	float		r2;
	t_cone		*cone;
	int			i;

	i = 0;
	while (i < mini->scene.cone_count)
	{
		cone = &mini->scene.cones[i];
		axis = vectors_unit(cone->vectors);
		r2 = cone->diameter / 2.0f;
		r2 *= r2;
		process_cone_intersections(ray, cone);
		process_cone_cap(ray, cone);
		i++;
	}
}
