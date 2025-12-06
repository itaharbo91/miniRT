/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_rotations_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:26:54 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/22 17:38:45 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

#define ROTATE_UP 119
#define ROTATE_DOWN 115
#define ROTATE_LEFT 97
#define ROTATE_RIGHT 100
#define ROTATE_Z_LEFT 113
#define ROTATE_Z_RIGHT 101

static void	cylinder_rotation(t_minirt *mini, int key, float angle)
{
	t_cylinder			*cylinder;
	t_transform_point	tp_axis;
	t_matrix			rotation_matrix;

	cylinder = &mini->scene.cylinders[mini->cmd.selected_cylinder];
	init_matrix(&rotation_matrix);
	if (key == ROTATE_UP)
		m_rotate_x(&rotation_matrix, -angle);
	else if (key == ROTATE_DOWN)
		m_rotate_x(&rotation_matrix, angle);
	else if (key == ROTATE_LEFT)
		m_rotate_y(&rotation_matrix, angle);
	else if (key == ROTATE_RIGHT)
		m_rotate_y(&rotation_matrix, -angle);
	else if (key == ROTATE_Z_LEFT)
		m_rotate_z(&rotation_matrix, -angle);
	else if (key == ROTATE_Z_RIGHT)
		m_rotate_z(&rotation_matrix, angle);
	tp_axis = point_to_transform_point(vector_to_point(cylinder->vectors));
	matrix_to_point(&rotation_matrix, &tp_axis);
	cylinder->vectors = point_to_vector(transform_point_to_point(tp_axis));
	cylinder->vectors = vectors_unit(cylinder->vectors);
}

static void	plane_rotation(t_minirt *mini, int key, float angle)
{
	t_plane				*plane;
	t_transform_point	tp_normal;
	t_matrix			rotation_matrix;

	plane = &mini->scene.planes[mini->cmd.selected_plane];
	init_matrix(&rotation_matrix);
	if (key == ROTATE_UP)
		m_rotate_x(&rotation_matrix, -angle);
	else if (key == ROTATE_DOWN)
		m_rotate_x(&rotation_matrix, angle);
	else if (key == ROTATE_LEFT)
		m_rotate_y(&rotation_matrix, angle);
	else if (key == ROTATE_RIGHT)
		m_rotate_y(&rotation_matrix, -angle);
	else if (key == ROTATE_Z_LEFT)
		m_rotate_z(&rotation_matrix, -angle);
	else if (key == ROTATE_Z_RIGHT)
		m_rotate_z(&rotation_matrix, angle);
	tp_normal = point_to_transform_point(vector_to_point(plane->vectors));
	matrix_to_point(&rotation_matrix, &tp_normal);
	plane->vectors = point_to_vector(transform_point_to_point(tp_normal));
	plane->vectors = vectors_unit(plane->vectors);
}

static void	cone_rotation(t_minirt *mini, int key, float angle)
{
	t_cone				*cone;
	t_transform_point	tp_axis;
	t_matrix			rotation_matrix;

	cone = &mini->scene.cones[mini->cmd.selected_cone];
	init_matrix(&rotation_matrix);
	if (key == ROTATE_UP)
		m_rotate_x(&rotation_matrix, -angle);
	else if (key == ROTATE_DOWN)
		m_rotate_x(&rotation_matrix, angle);
	else if (key == ROTATE_LEFT)
		m_rotate_y(&rotation_matrix, angle);
	else if (key == ROTATE_RIGHT)
		m_rotate_y(&rotation_matrix, -angle);
	else if (key == ROTATE_Z_LEFT)
		m_rotate_z(&rotation_matrix, -angle);
	else if (key == ROTATE_Z_RIGHT)
		m_rotate_z(&rotation_matrix, angle);
	tp_axis = point_to_transform_point(vector_to_point(cone->vectors));
	matrix_to_point(&rotation_matrix, &tp_axis);
	cone->vectors = point_to_vector(transform_point_to_point(tp_axis));
	cone->vectors = vectors_unit(cone->vectors);
}

void	apply_object_rotation(int key, t_minirt *mini, float angle)
{
	if (mini->cmd.mode == MODE_CYLINDER)
		cylinder_rotation(mini, key, angle);
	else if (mini->cmd.mode == MODE_PLANE)
		plane_rotation(mini, key, angle);
	else if (mini->cmd.mode == MODE_CONE)
		cone_rotation(mini, key, angle);
}
