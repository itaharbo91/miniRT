/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:30:43 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/04 20:39:28 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_camera(char *line, t_minirt *mini)
{
	int	i;

	i = 0;
	skip_spaces(line, &i);
	mini->scene.camera.id = "C";
	i++;
	skip_spaces(line, &i);
	point_conv(&line[i], mini, &mini->scene.camera.points, &i);
	skip_spaces(line, &i);
	if (vector_conv(&line[i], mini, &mini->scene.camera.vectors, &i) == 1)
		fatal_err("Camera vector must be between -1.0 and 1.0!", mini);
	skip_spaces(line, &i);
	if (fov_conv(&line[i], mini, &i) == 1)
		fatal_err("Camera FOV must be between 0 and 180!", mini);
	skip_spaces(line, &i);
	if (line[i] != '\n' && line[i] != '\0')
		fatal_err("Wrong character in camera!", mini);
}
