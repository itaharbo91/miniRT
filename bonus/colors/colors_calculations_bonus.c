/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_calculations_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:26:28 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/20 18:43:58 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

static t_color	calc_diffuse_color(t_color object_color, t_light_params params)
{
	t_color	diffuse;

	diffuse.r = (int)(object_color.r * (params.light_color.r / 255.0f)
			* params.intensity * params.ratio * params.attenuation);
	diffuse.g = (int)(object_color.g * (params.light_color.g / 255.0f)
			* params.intensity * params.ratio * params.attenuation);
	diffuse.b = (int)(object_color.b * (params.light_color.b / 255.0f)
			* params.intensity * params.ratio * params.attenuation);
	return (diffuse);
}

static float	calculate_light_intensity(t_light *light,
		t_intersection *intersection)
{
	float	intensity;

	intensity = vector_dot_product(intersection->normal,
			vectors_unit(light_dir_helper(light, intersection)));
	if (intensity < BIAS)
		intensity = 0.0f;
	return (intensity);
}

static t_color	calculate_diffuse_component(t_intersection *intersection,
		t_light *light, float intensity, float distance)
{
	t_light_params	light_params;

	light_params = (t_light_params){light->colors, intensity,
		light->ratio, attenuation_helper(distance)};
	return (calc_diffuse_color(intersection->color, light_params));
}

static t_color	calculate_light_contribution(t_minirt *mini,
		t_intersection *intersection, t_light *light)
{
	t_color	diffuse_color;
	t_color	specular_color;
	float	intensity;
	float	distance;

	distance = vector_magnitude(light_dir_helper(light, intersection));
	if (is_in_shadow_for_light(mini, intersection, light))
		return ((t_color){0, 0, 0});
	intensity = calculate_light_intensity(light, intersection);
	diffuse_color = calculate_diffuse_component(intersection, light,
			intensity, distance);
	specular_color = calculate_specular_component(mini, intersection, light);
	return (color_addition(diffuse_color, specular_color));
}

t_color	final_color_pixel(t_minirt *mini, t_intersection *intersection)
{
	t_color		final_color;
	t_color		ambient_color;
	t_color		light_contribution;
	t_color		object_color;
	int			i;

	object_color = get_object_color(intersection);
	intersection->color = object_color;
	ambient_color = color_multiplication(object_color,
			mini->scene.ambi_light.ratio);
	final_color = ambient_color;
	i = 0;
	while (i < mini->scene.light_count)
	{
		light_contribution = calculate_light_contribution(mini, intersection,
				&mini->scene.lights[i]);
		final_color = color_addition(final_color, light_contribution);
		i++;
	}
	return (clamp_color(final_color));
}
