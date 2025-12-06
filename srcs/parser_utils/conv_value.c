/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:47:02 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 19:02:16 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ratio_conv(char *line, t_minirt *mini, float *dst, int *i)
{
	char	*end;
	float	ratio;

	ratio = ft_strtof(line, &end);
	if (!ft_isdigit(end[0]) && !ft_isspace(end[0]))
		fatal_err("Invalid ratio format!", mini);
	if (ratio < 0.0f || ratio > 1.0f)
		return (1);
	*dst = ratio;
	*i += (end - line);
	return (0);
}

int	fov_conv(char *line, t_minirt *mini, int *i)
{
	int	fov;
	int	j;

	j = 0;
	if (!ft_isdigit(line[j]))
		fatal_err("Invalid fov format!", mini);
	fov = ft_atoi(&line[j]);
	while (line[j] && ft_isdigit(line[j]))
		j++;
	if (line[j] && !ft_isspace(line[j]) && line[j] != '\n')
		fatal_err("Invalid fov format!", mini);
	if (fov < 0 || fov > 180)
		return (1);
	mini->scene.camera.fov = fov;
	*i += j;
	return (0);
}

int	diameter_conv(char *line, t_minirt *mini, float *dst, int *i)
{
	char	*end;
	float	diameter;

	diameter = ft_strtof(line, &end);
	if (!ft_isdigit(end[0]) && !ft_isspace(end[0]))
		fatal_err("Invalid diameter format!", mini);
	if (diameter <= 0.0f)
		return (1);
	if (diameter > 10000.0f)
		fatal_err("Maximum accepted value for diameter is 10000.0f!", mini);
	*dst = diameter;
	*i += (end - line);
	return (0);
}

int	height_conv(char *line, t_minirt *mini, float *dst, int *i)
{
	char	*end;
	float	height;

	height = ft_strtof(line, &end);
	if (!ft_isdigit(end[0]) && !ft_isspace(end[0]))
		fatal_err("Invalid height format!", mini);
	if (height <= 0.0f)
		return (1);
	if (height > 10000.0f)
		fatal_err("Maximum accepted value for height is 10000.0f!", mini);
	*dst = height;
	*i += (end - line);
	return (0);
}
