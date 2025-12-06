/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:39:43 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/28 22:06:43 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include <unistd.h>

static void	free_objects(t_minirt *mini)
{
	if (mini->scene.spheres)
		free(mini->scene.spheres);
	if (mini->scene.planes)
		free(mini->scene.planes);
	if (mini->scene.cylinders)
		free(mini->scene.cylinders);
}

static void	free_data(t_minirt *mini)
{
	if (mini->data.img.img)
	{
		mlx_destroy_image(mini->data.mlx_ptr, mini->data.img.img);
		mini->data.img.img = NULL;
	}
	if (mini->data.win_ptr)
	{
		mlx_destroy_window(mini->data.mlx_ptr, mini->data.win_ptr);
		mini->data.win_ptr = NULL;
	}
	if (mini->data.mlx_ptr)
	{
		mlx_destroy_display(mini->data.mlx_ptr);
		free(mini->data.mlx_ptr);
		mini->data.mlx_ptr = NULL;
	}
}

void	free_minirt(t_minirt *mini)
{
	if (!mini)
		return ;
	cleanup_get_next_line();
	if (mini->current_line)
	{
		free(mini->current_line);
		mini->current_line = NULL;
	}
	if (mini->current_fd >= 0)
	{
		close(mini->current_fd);
		mini->current_fd = -1;
	}
	free_objects(mini);
	free_data(mini);
	if (mini)
		free(mini);
}
