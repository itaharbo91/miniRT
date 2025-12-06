/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_ray.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:29:15 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/16 21:54:14 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_RAY_H
# define MINIRT_RAY_H

# include "minirt_scene.h"

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_object_type;

typedef struct s_viewport
{
	float		width;
	float		height;
	float		fov;
	float		aspect_ratio;
	t_vector	forward;
	t_vector	right;
	t_vector	world_up;
	t_vector	u_cam;
	t_point		camera;
}	t_viewport;

typedef struct s_intersection
{
	void			*object;
	t_object_type	type;
	float			u;
	t_vector		point;
	t_vector		normal;
	float			distance2;
	t_color			color;
}	t_intersection;

typedef struct s_ray
{
	t_viewport		viewport;
	t_intersection	*intersections;
	int				intersection_count;
	t_vector		origin;
	t_vector		direction;
}	t_ray;

#endif
