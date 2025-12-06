/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:18:41 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/20 18:02:56 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	parse_sphere_helper(char *line, t_minirt *mini, int *i,
	int *sphere_nbr)
{
	skip_spaces(line, i);
	point_conv(&line[*i], mini, &mini->scene.spheres[*sphere_nbr].points, i);
	skip_spaces(line, i);
	if (diameter_conv(&line[*i], mini,
			&mini->scene.spheres[*sphere_nbr].diameter, i) == 1)
		fatal_err("Sphere diameter must be positive!", mini);
	skip_spaces(line, i);
	if (color_parse(&line[*i], mini,
			&mini->scene.spheres[*sphere_nbr].colors, i) == 1)
		fatal_err("Sphere colors must be between 0 and 255!", mini);
	skip_spaces(line, i);
	if (specular_conv(&line[*i], mini,
			&mini->scene.spheres[*sphere_nbr].specular, i) == 1)
		fatal_err("Sphere specular must be between 0.0 and 500.0!", mini);
	skip_spaces(line, i);
}

void	parse_sphere(char *line, t_minirt *mini)
{
	int	i;
	int	sphere_nbr;

	i = 0;
	sphere_nbr = mini->scene.sphere_count;
	skip_spaces(line, &i);
	mini->scene.spheres[sphere_nbr].id = "sp";
	mini->scene.sphere_count++;
	i += 2;
	parse_sphere_helper(line, mini, &i, &sphere_nbr);
	checkerboard_check(line[i],
		&mini->scene.spheres[sphere_nbr].checkerboard, mini);
	i++;
	if (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
		fatal_err("Wrong character in sphere!", mini);
	skip_spaces(line, &i);
	if (line[i] != '\n' && line[i] != '\0')
		fatal_err("Wrong character in sphere!", mini);
}
