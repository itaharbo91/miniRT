/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:26:28 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/17 18:16:20 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static t_color	calc_diffuse_color(t_color color, float intensity, float ratio,
		float attenuation)
{
	t_color	diffuse;

	diffuse.r = (int)(color.r * intensity * ratio * attenuation);
	diffuse.g = (int)(color.g * intensity * ratio * attenuation);
	diffuse.b = (int)(color.b * intensity * ratio * attenuation);
	return (diffuse);
}

static float	attenuation_helper(float distance)
{
	return (1.0f / (1.0f + 0.01f * distance + 0.001f * distance * distance));
}

t_color	final_color_pixel(t_minirt *mini, t_intersection *intersection)
{
	t_color		final_color;
	t_color		ambient_color;
	t_color		diffuse_color;
	float		intensity;
	float		distance;

	distance = vector_magnitude(light_dir_helper(mini, intersection));
	ambient_color = color_multiplication(intersection->color,
			mini->scene.ambi_light.ratio);
	if (is_in_shadow(mini, intersection))
		return (clamp_color(ambient_color));
	intensity = vector_dot_product(intersection->normal,
			vectors_unit(light_dir_helper(mini, intersection)));
	if (intensity < BIAS)
		intensity = 0.0f;
	diffuse_color = calc_diffuse_color(intersection->color, intensity,
			mini->scene.light.ratio, attenuation_helper(distance));
	final_color = color_addition(ambient_color, diffuse_color);
	return (clamp_color(final_color));
}
