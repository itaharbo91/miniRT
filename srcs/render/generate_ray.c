/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:13:11 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/17 17:20:43 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	generate_ray(t_minirt *mini, int i, int j)
{
	float		u;
	float		v;
	t_vector	p;
	t_vector	direction;

	u = (((float)i + 0.5f) / (float)mini->data.img.width - 0.5f)
		* mini->ray.viewport.width;
	v = (0.5f - ((float)j + 0.5f) / (float)mini->data.img.height)
		* mini->ray.viewport.height;
	mini->ray.origin = point_to_vector(mini->ray.viewport.camera);
	p = vector_addition(vector_addition(
				vector_addition(mini->ray.origin, mini->ray.viewport.forward),
				scalars_mult_by_vectors(u, mini->ray.viewport.right)),
			scalars_mult_by_vectors(v, mini->ray.viewport.u_cam));
	direction = vector_subtraction(p, mini->ray.origin);
	mini->ray.direction = vectors_unit(direction);
}

t_intersection	*get_closet_intersection(t_minirt *mini, t_ray *ray)
{
	int				i;
	t_intersection	*closest;

	(void)mini;
	if (ray->intersection_count == 0)
		return (NULL);
	closest = &ray->intersections[0];
	i = 1;
	while (i < ray->intersection_count)
	{
		if (ray->intersections[i].distance2 < closest->distance2)
			closest = &ray->intersections[i];
		i++;
	}
	return (closest);
}

bool	is_in_shadow(t_minirt *mini, t_intersection *intersection)
{
	t_vector		light_pos;
	t_vector		lvec;
	t_vector		p_bias;
	float			t_light;

	light_pos = point_to_vector(mini->scene.light.points);
	lvec = vector_subtraction(light_pos, intersection->point);
	t_light = vector_magnitude(lvec);
	p_bias = vector_addition(intersection->point,
			scalars_mult_by_vectors(BIAS, intersection->normal));
	mini->shadow_ray.origin = p_bias;
	mini->shadow_ray.direction = vectors_unit(lvec);
	mini->shadow_ray.intersection_count = 0;
	sphere_intersections(mini, &mini->shadow_ray);
	plane_intersections(mini, &mini->shadow_ray);
	cylinder_intersections(mini, &mini->shadow_ray);
	if (get_closet_intersection(mini, &mini->shadow_ray)
		&& get_closet_intersection(mini, &mini->shadow_ray)->u > EPSILON
		&& get_closet_intersection(mini, &mini->shadow_ray)->u
		< t_light - EPSILON)
		return (true);
	return (false);
}
