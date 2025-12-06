/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:12:33 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/16 17:25:39 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math.h"

t_color	color_transfer(t_color color)
{
	t_color	new_color;

	new_color.r = color.r;
	new_color.g = color.g;
	new_color.b = color.b;
	return (new_color);
}

t_color	color_addition(t_color a, t_color b)
{
	t_color	c;

	c.r = a.r + b.r;
	c.g = a.g + b.g;
	c.b = a.b + b.b;
	return (c);
}

t_color	color_multiplication(t_color a, float factor)
{
	t_color	c;

	c.r = (int)(a.r * factor);
	c.g = (int)(a.g * factor);
	c.b = (int)(a.b * factor);
	return (c);
}

t_color	clamp_color(t_color color)
{
	t_color	clamped;

	if (color.r > 255)
		clamped.r = 255;
	else if (color.r < 0)
		clamped.r = 0;
	else
		clamped.r = color.r;
	if (color.g > 255)
		clamped.g = 255;
	else if (color.g < 0)
		clamped.g = 0;
	else
		clamped.g = color.g;
	if (color.b > 255)
		clamped.b = 255;
	else if (color.b < 0)
		clamped.b = 0;
	else
		clamped.b = color.b;
	return (clamped);
}

t_vector	light_dir_helper(t_minirt *mini, t_intersection *intersection)
{
	t_vector	light_dir;

	light_dir = vector_subtraction(
			point_to_vector(mini->scene.light.points), intersection->point);
	return (light_dir);
}
