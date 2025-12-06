/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 23:29:30 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/16 21:53:53 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static void	fill_plane(t_ray *ray, t_plane *plane, float t)
{
	ray->intersections[ray->intersection_count].object = plane;
	ray->intersections[ray->intersection_count].type = PLANE;
	ray->intersections[ray->intersection_count].u = t;
	ray->intersections[ray->intersection_count].point = vector_addition(
			ray->origin, scalars_mult_by_vectors(t, ray->direction));
	ray->intersections[ray->intersection_count].normal
		= vectors_unit(plane->vectors);
	ray->intersections[ray->intersection_count].distance2 = t * t
		* vector_dot_product(ray->direction, ray->direction);
	ray->intersections[ray->intersection_count].color = plane->colors;
	ray->intersection_count++;
}

void	plane_intersections(t_minirt *mini, t_ray *ray)
{
	t_plane	*plane;
	float	dir;
	float	dist;
	float	t;
	int		i;

	i = 0;
	while (i < mini->scene.plane_count)
	{
		plane = &mini->scene.planes[i];
		dir = vector_dot_product(ray->direction, plane->vectors);
		if (fabs(dir) < EPSILON)
		{
			i++;
			continue ;
		}
		dist = vector_dot_product(plane->vectors,
				vector_subtraction(
					point_to_vector(plane->points), ray->origin));
		t = dist / dir;
		if (t > EPSILON)
			fill_plane(ray, plane, t);
		i++;
	}
}
