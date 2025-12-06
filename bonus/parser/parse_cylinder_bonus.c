/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:20:11 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/20 18:04:36 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	parse_cylinder_helper(char *line, t_minirt *mini, int *i,
	int *cylinder_nbr)
{
	skip_spaces(line, i);
	point_conv(&line[*i], mini,
		&mini->scene.cylinders[*cylinder_nbr].points, i);
	skip_spaces(line, i);
	if (vector_conv(&line[*i], mini,
			&mini->scene.cylinders[*cylinder_nbr].vectors, i) == 1)
		fatal_err("Cylinder vector must be between -1.0 and 1.0!", mini);
	skip_spaces(line, i);
	if (diameter_conv(&line[*i], mini,
			&mini->scene.cylinders[*cylinder_nbr].diameter, i) == 1)
		fatal_err("Cylinder diameter must be positive!", mini);
	skip_spaces(line, i);
	if (height_conv(&line[*i], mini,
			&mini->scene.cylinders[*cylinder_nbr].height, i) == 1)
		fatal_err("Cylinder height must be positive!", mini);
	skip_spaces(line, i);
	if (color_parse(&line[*i], mini,
			&mini->scene.cylinders[*cylinder_nbr].colors, i) == 1)
		fatal_err("Cylinder colors must be between 0 and 255!", mini);
	skip_spaces(line, i);
	if (specular_conv(&line[*i], mini,
			&mini->scene.cylinders[*cylinder_nbr].specular, i) == 1)
		fatal_err("Cylinder specular must be between 0.0 and 500.0!", mini);
	skip_spaces(line, i);
}

void	parse_cylinder(char *line, t_minirt *mini)
{
	int	i;
	int	cylinder_nbr;

	i = 0;
	cylinder_nbr = mini->scene.cylinder_count;
	skip_spaces(line, &i);
	mini->scene.cylinders[cylinder_nbr].id = "cy";
	mini->scene.cylinder_count++;
	i += 2;
	parse_cylinder_helper(line, mini, &i, &cylinder_nbr);
	checkerboard_check(line[i],
		&mini->scene.cylinders[cylinder_nbr].checkerboard, mini);
	i++;
	if (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
		fatal_err("Wrong character in cylinder!", mini);
	skip_spaces(line, &i);
	if (line[i] != '\n' && line[i] != '\0')
		fatal_err("Wrong character in cylinder!", mini);
}
