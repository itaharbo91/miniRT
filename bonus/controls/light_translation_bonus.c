/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_translation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 21:08:38 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/28 21:09:32 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

#define UP 65362
#define DOWN 65364
#define LEFT 65361
#define RIGHT 65363
#define FORWARD 120
#define BACKWARD 122

void	light_translation(t_minirt *mini, int key, float delta)
{
	t_vector	move;
	t_light		*light;

	light = &mini->scene.lights[0];
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
