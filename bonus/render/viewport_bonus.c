/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:32:57 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 19:54:25 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

static void	viewport_world_up(t_minirt *mini)
{
	mini->ray.viewport.world_up.vect_x = 0.0f;
	mini->ray.viewport.world_up.vect_y = 1.0f;
	mini->ray.viewport.world_up.vect_z = 0.0f;
	if (fabs(vector_dot_product(mini->ray.viewport.forward,
				mini->ray.viewport.world_up)) > 0.999f)
	{
		mini->ray.viewport.world_up.vect_x = 1.0f;
		mini->ray.viewport.world_up.vect_y = 0.0f;
		mini->ray.viewport.world_up.vect_z = 0.0f;
	}
}

void	camera_cues(t_minirt *mini)
{
	t_transform_point	camera_dir;

	mini->ray.viewport.camera = mini->scene.camera.points;
	mini->ray.viewport.forward = vectors_unit(mini->scene.camera.vectors);
	camera_dir = point_to_transform_point((t_point){
			mini->ray.viewport.forward.vect_x,
			mini->ray.viewport.forward.vect_y,
			mini->ray.viewport.forward.vect_z
		});
	matrix_to_point(&mini->cmd.rot_matrix, &camera_dir);
	mini->ray.viewport.forward = (t_vector){
		camera_dir.x,
		camera_dir.y,
		camera_dir.z
	};
	mini->ray.viewport.forward = vectors_unit(mini->ray.viewport.forward);
	viewport_world_up(mini);
	mini->ray.viewport.right = vectors_unit(
			vector_cross_products(mini->ray.viewport.forward,
				mini->ray.viewport.world_up));
	mini->ray.viewport.u_cam = vectors_unit(vector_cross_products(
				mini->ray.viewport.right, mini->ray.viewport.forward));
}

void	viewport(t_minirt *mini)
{
	int	image_width;
	int	image_height;

	image_width = mini->data.img.width;
	image_height = mini->data.img.height;
	mini->ray.viewport.fov = mini->scene.camera.fov * (M_PI / 180.0f);
	mini->ray.viewport.width = 2 * (tanf(mini->ray.viewport.fov / 2.0f));
	mini->ray.viewport.aspect_ratio = (float)image_width / (float)image_height;
	mini->ray.viewport.height = mini->ray.viewport.width
		/ mini->ray.viewport.aspect_ratio;
}
