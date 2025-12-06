/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_equations_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:34:57 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 19:25:31 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

t_vector	sp_param_ray_equa(t_vector origin, float u, t_vector direction)
{
	t_vector	p;

	if (u < EPSILON)
	{
		p.vect_x = origin.vect_x;
		p.vect_y = origin.vect_y;
		p.vect_z = origin.vect_z;
		return (p);
	}
	p.vect_x = origin.vect_x + u * direction.vect_x;
	p.vect_y = origin.vect_y + u * direction.vect_y;
	p.vect_z = origin.vect_z + u * direction.vect_z;
	return (p);
}

float	sp_surface_equation(t_vector origin, float u, t_vector direction,
		t_vector center)
{
	t_vector	p;
	float		r;

	p = sp_param_ray_equa(origin, u, direction);
	r = (p.vect_x - center.vect_x) * (p.vect_x - center.vect_x)
		+ (p.vect_y - center.vect_y) * (p.vect_y - center.vect_y)
		+ (p.vect_z - center.vect_z) * (p.vect_z - center.vect_z);
	return (r);
}

t_point	sp_surf_inters_delta(t_vector direction, t_vector origin,
		t_vector center, float r)
{
	t_point	abc;

	abc.x = vector_dot_product(direction, direction);
	abc.y = 2 * vector_dot_product(direction,
			vector_subtraction(origin, center));
	abc.z = vector_dot_product(vector_subtraction(origin, center),
			vector_subtraction(origin, center)) - r;
	return (abc);
}

float	sp_ray_surf_inters(t_vector origin, t_vector direction,
		t_vector center, float r)
{
	t_point	abc;
	float	delta;
	float	u1;
	float	u2;

	abc = sp_surf_inters_delta(direction, origin, center, r);
	delta = abc.y * abc.y - 4.0f * abc.x * abc.z;
	if (delta < 0.0f)
		return (-1.0f);
	u1 = (-abc.y - sqrtf(delta)) / (2.0f * abc.x);
	u2 = (-abc.y + sqrtf(delta)) / (2.0f * abc.x);
	if (u1 > EPSILON && (u2 < EPSILON || u1 < u2))
		return (u1);
	if (u2 > EPSILON)
		return (u2);
	return (-1.0f);
}

t_vector	sp_surf_normal_vector(t_vector direction, t_vector origin,
		t_vector center, float u)
{
	t_vector	p;
	t_vector	n;

	p = sp_param_ray_equa(origin, u, direction);
	n.vect_x = p.vect_x - center.vect_x;
	n.vect_y = p.vect_y - center.vect_y;
	n.vect_z = p.vect_z - center.vect_z;
	n = vectors_unit(n);
	if (vector_dot_product(n, direction) > 0)
		n = scalars_mult_by_vectors(-1.0f, n);
	return (n);
}
