/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 23:03:19 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 21:28:43 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_light(char *line, t_minirt *mini)
{
	int	i;

	i = 0;
	skip_spaces(line, &i);
	mini->scene.light.id = "L";
	i++;
	skip_spaces(line, &i);
	point_conv(&line[i], mini, &mini->scene.light.points, &i);
	skip_spaces(line, &i);
	if (ratio_conv(&line[i], mini, &mini->scene.light.ratio, &i) == 1)
		fatal_err("Light ratio must be between 0.0 and 1.0!", mini);
	skip_spaces(line, &i);
	if (line[i] != '\n' && line[i] != '\0')
		fatal_err("Wrong character in light!", mini);
}
