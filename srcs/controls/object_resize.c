/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:12:03 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/17 18:17:37 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

#define INCREASE 65451
#define DECREASE 65453
#define INCREASE_HEIGHT 110
#define DECREASE_HEIGHT 109

static void	sphere_resize(t_minirt *mini, float delta, int key)
{
	t_sphere	*sphere;

	sphere = &mini->scene.spheres[mini->cmd.selected_sphere];
	if (key == INCREASE)
		sphere->diameter += delta;
	else if (key == DECREASE)
		sphere->diameter -= delta;
	if (sphere->diameter < 0.1f)
		sphere->diameter = 0.1f;
}

static void	cylinder_resize(t_minirt *mini, float delta, int key)
{
	t_cylinder	*cylinder;

	cylinder = &mini->scene.cylinders[mini->cmd.selected_cylinder];
	if (key == INCREASE)
		cylinder->diameter += delta;
	else if (key == DECREASE)
		cylinder->diameter -= delta;
	if (cylinder->diameter < 0.1f)
		cylinder->diameter = 0.1f;
	if (key == INCREASE_HEIGHT)
		cylinder->height += delta;
	else if (key == DECREASE_HEIGHT)
		cylinder->height -= delta;
	if (cylinder->height < 0.1f)
		cylinder->height = 0.1f;
}

void	apply_object_resize(int key, t_minirt *mini)
{
	float	delta;

	delta = 0.1f;
	if (mini->cmd.mode == MODE_SPHERE)
		sphere_resize(mini, delta, key);
	else if (mini->cmd.mode == MODE_CYLINDER)
		cylinder_resize(mini, delta, key);
}
