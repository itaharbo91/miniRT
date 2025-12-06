/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_pointer_values_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:02:59 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 19:48:47 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	isvalid_points(t_minirt *mini, float x, float y, float z)
{
	if (x < -10000.0f || x > 10000.0f)
		fatal_err("Point x value is out of range (-10000.0 to 10000.0)!", mini);
	if (y < -10000.0f || y > 10000.0f)
		fatal_err("Point y value is out of range (-10000.0 to 10000.0)!", mini);
	if (z < -10000.0f || z > 10000.0f)
		fatal_err("Point z value is out of range (-10000.0 to 10000.0)!", mini);
}

static void	point_conv_helper(char *line, t_minirt *mini, char *end, int *j)
{
	if (!ft_isdigit(end[0]) && end[0] != ',')
		fatal_err("Invalid point format!", mini);
	*j += (end - &line[*j]);
	(*j)++;
}

void	point_conv(char *line, t_minirt *mini, t_point *dst, int *i)
{
	char	*end;
	float	x;
	float	y;
	float	z;
	int		j;

	j = 0;
	x = ft_strtof(&line[j], &end);
	point_conv_helper(line, mini, end, &j);
	y = ft_strtof(&line[j], &end);
	point_conv_helper(line, mini, end, &j);
	if (!ft_isdigit(line[j]) && line[j] != '-' && line[j] != '+')
		fatal_err("Invalid point format!", mini);
	z = ft_strtof(&line[j], &end);
	if (!ft_isdigit(end[0]) && !ft_isspace(end[0]) && end[0] != '\n')
		fatal_err("Invalid point format!", mini);
	isvalid_points(mini, x, y, z);
	j += (end - &line[j]);
	dst->x = x;
	dst->y = y;
	dst->z = z;
	*i += j;
}

static void	vector_conv_helper(char *line, t_minirt *mini, char *end, int *j)
{
	if (!ft_isdigit(end[0]) && end[0] != ',')
		fatal_err("Invalid vector format!", mini);
	*j += (end - &line[*j]);
	(*j)++;
}

int	vector_conv(char *line, t_minirt *mini, t_vector *dst, int *i)
{
	char	*end;
	float	vect_x;
	float	vect_y;
	float	vect_z;
	int		j;

	j = 0;
	vect_x = ft_strtof(&line[j], &end);
	vector_conv_helper(line, mini, end, &j);
	vect_y = ft_strtof(&line[j], &end);
	vector_conv_helper(line, mini, end, &j);
	if (!ft_isdigit(line[j]) && line[j] != '-' && line[j] != '+')
		fatal_err("Invalid vector format!", mini);
	vect_z = ft_strtof(&line[j], &end);
	if (!ft_isspace(end[0]) && end[0] != '\n')
		fatal_err("Invalid vector format!", mini);
	j += (end - &line[j]);
	if (vect_x < -1.0f || vect_x > 1.0f || vect_y < -1.0f || vect_y > 1.0f
		|| vect_z < -1.0f || vect_z > 1.0f)
		return (1);
	dst->vect_x = vect_x;
	dst->vect_y = vect_y;
	dst->vect_z = vect_z;
	*i += j;
	return (0);
}
