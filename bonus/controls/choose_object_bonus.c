/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_object_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:24:53 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/28 21:15:08 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_point	vector_to_point(t_vector v)
{
	t_point	p;

	p.x = v.vect_x;
	p.y = v.vect_y;
	p.z = v.vect_z;
	return (p);
}

static void	forward_helper(t_minirt *mini, t_cmd *cmd, int count)
{
	if (cmd->mode == MODE_PLANE)
	{
		count = mini->scene.plane_count;
		if (count > 0)
			cmd->selected_plane = (cmd->selected_plane + 1) % count;
	}
	else if (cmd->mode == MODE_CONE)
	{
		count = mini->scene.cone_count;
		if (count > 0)
			cmd->selected_cone = (cmd->selected_cone + 1) % count;
	}
	else if (cmd->mode == MODE_LIGHT)
	{
		count = mini->scene.light_count;
		if (count > 0)
			cmd->selected_light = (cmd->selected_light + 1) % count;
	}
}

void	cycle_object_forward(t_minirt *mini)
{
	t_cmd	*cmd;
	int		count;

	cmd = &mini->cmd;
	count = 0;
	if (cmd->mode == MODE_SPHERE)
	{
		count = mini->scene.sphere_count;
		if (count > 0)
			cmd->selected_sphere = (cmd->selected_sphere + 1) % count;
	}
	else if (cmd->mode == MODE_CYLINDER)
	{
		count = mini->scene.cylinder_count;
		if (count > 0)
			cmd->selected_cylinder = (cmd->selected_cylinder + 1) % count;
	}
	else
		forward_helper(mini, cmd, count);
}

static void	backward_helper(t_minirt *mini, t_cmd *cmd, int count)
{
	if (cmd->mode == MODE_PLANE)
	{
		count = mini->scene.plane_count;
		if (count > 0)
			cmd->selected_plane = (cmd->selected_plane - 1 + count) % count;
	}
	else if (cmd->mode == MODE_CONE)
	{
		count = mini->scene.cone_count;
		if (count > 0)
			cmd->selected_cone = (cmd->selected_cone - 1 + count) % count;
	}
	else if (cmd->mode == MODE_LIGHT)
	{
		count = mini->scene.light_count;
		if (count > 0)
			cmd->selected_light = (cmd->selected_light - 1 + count) % count;
	}
}

void	cycle_object_backward(t_minirt *mini)
{
	t_cmd	*cmd;
	int		count;

	cmd = &mini->cmd;
	count = 0;
	if (cmd->mode == MODE_SPHERE)
	{
		count = mini->scene.sphere_count;
		if (count > 0)
			cmd->selected_sphere = (cmd->selected_sphere - 1 + count) % count;
	}
	else if (cmd->mode == MODE_CYLINDER)
	{
		count = mini->scene.cylinder_count;
		if (count > 0)
			cmd->selected_cylinder = (cmd->selected_cylinder - 1 + count)
				% count;
	}
	else
		backward_helper(mini, cmd, count);
}
