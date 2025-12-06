/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_equations_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:21:30 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/29 14:35:10 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

static float	cos2_theta_calc(t_cone *cone)
{
	float	k;
	float	cos_theta;
	float	cos2_theta;

	k = (cone->diameter / 2.0f) / cone->height;
	cos_theta = 1.0f / sqrtf(1.0f + k * k);
	cos2_theta = cos_theta * cos_theta;
	return (cos2_theta);
}

float	a_discriminant(t_ray *ray, t_cone *cone)
{
	float	cos2_theta;
	float	dv;
	float	dd;

	cos2_theta = cos2_theta_calc(cone);
	dv = vector_dot_product(vectors_unit(ray->direction),
			vectors_unit(cone->vectors));
	dd = vector_dot_product(vectors_unit(ray->direction),
			vectors_unit(ray->direction));
	return (dv * dv - cos2_theta * dd);
}

float	b_discriminant(t_ray *ray, t_cone *cone)
{
	float		cos2_theta;
	t_vector	co;
	float		dv;
	float		cov;
	float		dco;

	cos2_theta = cos2_theta_calc(cone);
	co = vector_subtraction(ray->origin, point_to_vector(cone->points));
	dv = vector_dot_product(vectors_unit(ray->direction),
			vectors_unit(cone->vectors));
	cov = vector_dot_product(co, vectors_unit(cone->vectors));
	dco = vector_dot_product(vectors_unit(ray->direction), co);
	return (2.0f * (dv * cov - cos2_theta * dco));
}

float	c_discriminant(t_ray *ray, t_cone *cone)
{
	float		cos2_theta;
	t_vector	co;
	float		cov;
	float		coco;

	cos2_theta = cos2_theta_calc(cone);
	co = vector_subtraction(ray->origin, point_to_vector(cone->points));
	cov = vector_dot_product(co, vectors_unit(cone->vectors));
	coco = vector_dot_product(co, co);
	return (cov * cov - cos2_theta * coco);
}

void	t_choose_fill(t_ray *ray, t_cone *cone, float t)
{
	t_vector	p;
	float		dist_to_apex;
	float		dot;

	p = vector_addition(ray->origin, scalars_mult_by_vectors(t,
				vectors_unit(ray->direction)));
	dot = vector_dot_product(vector_subtraction(p,
				point_to_vector(cone->points)),
			vectors_unit(cone->vectors));
	dist_to_apex = vector_length(vector_subtraction(p,
				point_to_vector(cone->points)));
	if (dist_to_apex > 0.005f && dot > 0 && check_cone_height(p, cone))
		cone_fill(ray, cone, t);
}
