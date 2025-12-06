/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_scene.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:18:43 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 21:28:58 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_SCENE_H
# define MINIRT_SCENE_H

# include <stdbool.h>

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_vector
{
	float	vect_x;
	float	vect_y;
	float	vect_z;
}	t_vector;

typedef struct s_ambi_light
{
	char	*id;
	float	ratio;
	t_color	colors;
}	t_ambi_light;

typedef struct s_camera
{
	char		*id;
	t_point		points;
	t_vector	vectors;
	int			fov;
}	t_camera;

typedef struct s_light
{
	char	*id;
	t_point	points;
	float	ratio;
}	t_light;

typedef struct s_sphere
{
	char	*id;
	t_point	points;
	float	diameter;
	t_color	colors;
}	t_sphere;

typedef struct s_plane
{
	char		*id;
	t_point		points;
	t_vector	vectors;
	t_color		colors;
}	t_plane;

typedef struct s_cylinder
{
	char		*id;
	t_point		points;
	t_vector	vectors;
	float		diameter;
	float		height;
	t_color		colors;
}	t_cylinder;

typedef struct s_scene
{
	t_ambi_light	ambi_light;
	int				ambi_light_count;
	t_camera		camera;
	int				camera_count;
	t_light			light;
	int				light_count;
	t_sphere		*spheres;
	int				sphere_count;
	t_plane			*planes;
	int				plane_count;
	t_cylinder		*cylinders;
	int				cylinder_count;
	int				object_count;
}	t_scene;

#endif
