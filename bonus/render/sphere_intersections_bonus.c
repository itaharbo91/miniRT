/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersections_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:03:16 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 19:54:08 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	fill_sphere(t_ray *ray, t_vector center, float u, t_sphere *sphere)
{
	ray->intersections[ray->intersection_count].object = sphere;
	ray->intersections[ray->intersection_count].type = SPHERE;
	ray->intersections[ray->intersection_count].u = u;
	ray->intersections[ray->intersection_count].point
		= sp_param_ray_equa(ray->origin, u, ray->direction);
	ray->intersections[ray->intersection_count].normal
		= sp_surf_normal_vector(ray->direction, ray->origin, center, u);
	ray->intersections[ray->intersection_count].distance2
		= u * u * vector_dot_product(ray->direction, ray->direction);
	ray->intersections[ray->intersection_count].color = sphere->colors;
	ray->intersections[ray->intersection_count].specular = sphere->specular;
}

void	sphere_intersections(t_minirt *mini, t_ray *ray)
{
	int			i;
	float		u;
	t_sphere	*sphere;
	t_vector	center;
	float		r2;

	i = 0;
	while (i < mini->scene.sphere_count)
	{
		sphere = &mini->scene.spheres[i];
		r2 = (sphere->diameter / 2.0f) * (sphere->diameter / 2.0f);
		center = point_to_vector(sphere->points);
		u = sp_ray_surf_inters(ray->origin, ray->direction, center, r2);
		if (u > EPSILON)
		{
			fill_sphere(ray, center, u, sphere);
			if (ray->intersections[ray->intersection_count].distance2 < 0.0f)
				fatal_err("sphere_intersections: negative distance", mini);
			ray->intersection_count++;
		}
		i++;
	}
}
