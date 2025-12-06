/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:19:25 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/20 18:03:54 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	parse_plane_helper(char *line, t_minirt *mini, int *i,
	int *plane_nbr)
{
	skip_spaces(line, i);
	point_conv(&line[*i], mini,
		&mini->scene.planes[*plane_nbr].points, i);
	skip_spaces(line, i);
	if (vector_conv(&line[*i], mini,
			&mini->scene.planes[*plane_nbr].vectors, i) == 1)
		fatal_err("Plane vector must be between -1.0 and 1.0!", mini);
	skip_spaces(line, i);
	if (color_parse(&line[*i], mini,
			&mini->scene.planes[*plane_nbr].colors, i) == 1)
		fatal_err("Plane colors must be between 0 and 255!", mini);
	skip_spaces(line, i);
	if (specular_conv(&line[*i], mini,
			&mini->scene.planes[*plane_nbr].specular, i) == 1)
		fatal_err("Plane specular must be between 0.0 and 500.0!", mini);
	skip_spaces(line, i);
}

void	parse_plane(char *line, t_minirt *mini)
{
	int	i;
	int	plane_nbr;

	i = 0;
	plane_nbr = mini->scene.plane_count;
	skip_spaces(line, &i);
	mini->scene.planes[plane_nbr].id = "pl";
	mini->scene.plane_count++;
	i += 2;
	parse_plane_helper(line, mini, &i, &plane_nbr);
	checkerboard_check(line[i],
		&mini->scene.planes[plane_nbr].checkerboard, mini);
	i++;
	if (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
		fatal_err("Wrong character in plane!", mini);
	skip_spaces(line, &i);
	if (line[i] != '\n' && line[i] != '\0')
		fatal_err("Wrong character in plane!", mini);
}
