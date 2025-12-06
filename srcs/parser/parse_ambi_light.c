/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambi_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:00:55 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/04 20:40:04 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambi_light(char *line, t_minirt *mini)
{
	int	i;

	i = 0;
	skip_spaces(line, &i);
	mini->scene.ambi_light.id = "A";
	i++;
	skip_spaces(line, &i);
	if (ratio_conv(&line[i], mini, &mini->scene.ambi_light.ratio, &i) == 1)
		fatal_err("Ambient lighting ratio must be between 0.0 and 1.0!", mini);
	skip_spaces(line, &i);
	if (color_parse(&line[i], mini, &mini->scene.ambi_light.colors, &i) == 1)
		fatal_err("Ambient lighting colors must be between 0 and 255!", mini);
	skip_spaces(line, &i);
	if (line[i] != '\n' && line[i] != '\0')
		fatal_err("Wrong character in ambient lighting!", mini);
}
