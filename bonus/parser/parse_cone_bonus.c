/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:19:35 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/22 17:23:34 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	parse_cone_helper(char *line, t_minirt *mini, int *i,
	int *cone_nbr)
{
	skip_spaces(line, i);
	point_conv(&line[*i], mini, &mini->scene.cones[*cone_nbr].points, i);
	skip_spaces(line, i);
	if (vector_conv(&line[*i], mini,
			&mini->scene.cones[*cone_nbr].vectors, i) == 1)
		fatal_err("Cone vector must be between -1.0 and 1.0!", mini);
	skip_spaces(line, i);
	if (diameter_conv(&line[*i], mini,
			&mini->scene.cones[*cone_nbr].diameter, i) == 1)
		fatal_err("Cone diameter must be positive!", mini);
	skip_spaces(line, i);
	if (height_conv(&line[*i], mini,
			&mini->scene.cones[*cone_nbr].height, i) == 1)
		fatal_err("Cone height must be positive!", mini);
	skip_spaces(line, i);
	if (color_parse(&line[*i], mini,
			&mini->scene.cones[*cone_nbr].colors, i) == 1)
		fatal_err("Cone colors must be between 0 and 255!", mini);
	skip_spaces(line, i);
	if (specular_conv(&line[*i], mini,
			&mini->scene.cones[*cone_nbr].specular, i) == 1)
		fatal_err("Cone specular must be between 0.0 and 500.0!", mini);
	skip_spaces(line, i);
}

void	parse_cone(char *line, t_minirt *mini)
{
	int	i;
	int	cone_nbr;

	i = 0;
	cone_nbr = mini->scene.cone_count;
	skip_spaces(line, &i);
	mini->scene.cones[cone_nbr].id = "co";
	mini->scene.cone_count++;
	i += 2;
	parse_cone_helper(line, mini, &i, &cone_nbr);
	checkerboard_check(line[i],
		&mini->scene.cones[cone_nbr].checkerboard, mini);
	i++;
	if (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
		fatal_err("Wrong character in cone!", mini);
	skip_spaces(line, &i);
	if (line[i] != '\n' && line[i] != '\0')
		fatal_err("Wrong character in cone!", mini);
}
