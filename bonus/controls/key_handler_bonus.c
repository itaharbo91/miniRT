/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:41:52 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/22 17:34:00 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#define ESC 65307
#define UP 65362
#define DOWN 65364
#define LEFT 65361
#define RIGHT 65363
#define INCREASE 65451
#define DECREASE 65453
#define ROTATE_UP 119
#define ROTATE_DOWN 115
#define ROTATE_LEFT 97
#define ROTATE_RIGHT 100
#define ROTATE_Z_LEFT 113
#define ROTATE_Z_RIGHT 101
#define FORWARD 120
#define BACKWARD 122

#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define TAB 65289
#define SHIFT_TAB 65056

void	apply_camera_translation(int key, t_minirt *mini, float delta)
{
	t_vector	move;

	move = (t_vector){0, 0, 0};
	if (key == LEFT)
		move = scalars_mult_by_vectors(-delta, mini->ray.viewport.right);
	else if (key == RIGHT)
		move = scalars_mult_by_vectors(delta, mini->ray.viewport.right);
	else if (key == DOWN)
		move = scalars_mult_by_vectors(-delta, mini->ray.viewport.u_cam);
	else if (key == UP)
		move = scalars_mult_by_vectors(delta, mini->ray.viewport.u_cam);
	else if (key == FORWARD)
		move = scalars_mult_by_vectors(delta, mini->ray.viewport.forward);
	else if (key == BACKWARD)
		move = scalars_mult_by_vectors(-delta, mini->ray.viewport.forward);
	mini->scene.camera.points = vector_to_point(
			vector_addition(point_to_vector(mini->scene.camera.points), move));
}

void	handle_translation(int key, t_minirt *mini)
{
	float	delta;

	delta = 0.2f;
	if (mini->cmd.mode == MODE_CAMERA)
		apply_camera_translation(key, mini, delta);
	else
		apply_object_translation(key, mini, delta);
}

void	handle_rotation(int key, t_minirt *mini)
{
	float		angle;
	t_matrix	tmp_matrix;

	init_matrix(&tmp_matrix);
	angle = 0.02f;
	if (mini->cmd.mode == MODE_CAMERA)
	{
		if (key == ROTATE_UP)
			m_rotate_x(&tmp_matrix, -angle);
		else if (key == ROTATE_DOWN)
			m_rotate_x(&tmp_matrix, angle);
		else if (key == ROTATE_LEFT)
			m_rotate_y(&tmp_matrix, angle);
		else if (key == ROTATE_RIGHT)
			m_rotate_y(&tmp_matrix, -angle);
		else if (key == ROTATE_Z_LEFT)
			m_rotate_z(&tmp_matrix, -angle);
		else if (key == ROTATE_Z_RIGHT)
			m_rotate_z(&tmp_matrix, angle);
		multiply_matrix(&mini->cmd.rot_matrix, &tmp_matrix);
	}
	else
		apply_object_rotation(key, mini, angle);
}

void	handle_mode_selection(int key, t_minirt *mini)
{
	if (key == KEY_1)
		mini->cmd.mode = MODE_CAMERA;
	else if (key == KEY_2)
		mini->cmd.mode = MODE_SPHERE;
	else if (key == KEY_3)
		mini->cmd.mode = MODE_CYLINDER;
	else if (key == KEY_4)
		mini->cmd.mode = MODE_PLANE;
	else if (key == KEY_5)
		mini->cmd.mode = MODE_CONE;
	else if (key == KEY_6)
		mini->cmd.mode = MODE_LIGHT;
}

void	handle_object_selection(int key, t_minirt *mini)
{
	if (key == TAB)
		cycle_object_forward(mini);
	else if (key == SHIFT_TAB)
		cycle_object_backward(mini);
}
