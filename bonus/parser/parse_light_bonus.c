/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 23:03:19 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 21:49:06 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	parse_light(char *line, t_minirt *mini)
{
	int	i;
	int	light_index;

	i = 0;
	light_index = mini->scene.light_count;
	skip_spaces(line, &i);
	mini->scene.lights[light_index].id = "L";
	i++;
	skip_spaces(line, &i);
	point_conv(&line[i], mini, &mini->scene.lights[light_index].points, &i);
	skip_spaces(line, &i);
	if (ratio_conv(&line[i], mini, &mini->scene.lights[light_index].ratio,
			&i) == 1)
		fatal_err("Light ratio must be between 0.0 and 1.0!", mini);
	skip_spaces(line, &i);
	if (color_parse(&line[i], mini, &mini->scene.lights[light_index].colors,
			&i) == 1)
		fatal_err("Light colors must be between 0 and 255!", mini);
	skip_spaces(line, &i);
	if (line[i] != '\n' && line[i] != '\0')
		fatal_err("Wrong character in light!", mini);
	mini->scene.light_count++;
}
