/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_translations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:23:51 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/17 18:19:11 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <math.h>

#define UP 65362
#define DOWN 65364
#define LEFT 65361
#define RIGHT 65363
#define FORWARD 120
#define BACKWARD 122

static void	sphere_translation(t_minirt *mini, int key, float delta)
{
	t_vector	move;
	t_sphere	*sphere;

	sphere = &mini->scene.spheres[mini->cmd.selected_sphere];
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
	sphere->points = vector_to_point(
			vector_addition(point_to_vector(sphere->points), move));
}

static void	cylinder_translation(t_minirt *mini, int key, float delta)
{
	t_vector	move;
	t_cylinder	*cylinder;

	cylinder = &mini->scene.cylinders[mini->cmd.selected_cylinder];
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
	cylinder->points = vector_to_point(
			vector_addition(point_to_vector(cylinder->points), move));
}

static void	plane_translation(t_minirt *mini, int key, float delta)
{
	t_vector	move;
	t_plane		*plane;

	plane = &mini->scene.planes[mini->cmd.selected_plane];
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
	plane->points = vector_to_point(
			vector_addition(point_to_vector(plane->points), move));
}

static void	light_translation(t_minirt *mini, int key, float delta)
{
	t_vector	move;
	t_light		*light;

	light = &mini->scene.light;
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
	light->points = vector_to_point(
			vector_addition(point_to_vector(light->points), move));
}

void	apply_object_translation(int key, t_minirt *mini, float delta)
{
	if (mini->cmd.mode == MODE_SPHERE)
		sphere_translation(mini, key, delta);
	else if (mini->cmd.mode == MODE_CYLINDER)
		cylinder_translation(mini, key, delta);
	else if (mini->cmd.mode == MODE_PLANE)
		plane_translation(mini, key, delta);
	else if (mini->cmd.mode == MODE_LIGHT)
		light_translation(mini, key, delta);
}
