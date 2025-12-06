/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:50:38 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/04 21:03:29 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	color_parse_helper(char *line, t_minirt *mini, int *j)
{
	int	val;

	if (!ft_isdigit(line[*j]))
		fatal_err("Invalid color format!", mini);
	val = ft_atoi(&line[*j]);
	while (line[*j] && ft_isdigit(line[*j]))
		(*j)++;
	return (val);
}

int	color_parse(char *line, t_minirt *mini, t_color *dst, int *i)
{
	int		r;
	int		g;
	int		b;
	int		j;

	j = 0;
	r = color_parse_helper(line, mini, &j);
	if (line[j] != ',')
		fatal_err("Invalid color format!", mini);
	j++;
	g = color_parse_helper(line, mini, &j);
	if (line[j] != ',')
		fatal_err("Invalid color format!", mini);
	j++;
	b = color_parse_helper(line, mini, &j);
	if (line[j] && !ft_isspace(line[j]) && line[j] != '\n')
		fatal_err("Invalid color format!", mini);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	dst->r = r;
	dst->g = g;
	dst->b = b;
	*i += j;
	return (0);
}
