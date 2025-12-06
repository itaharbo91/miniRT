/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_color_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:39:47 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 21:46:45 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

float	attenuation_helper(float distance)
{
	return (1.0f / (1.0f + 0.01f * distance + 0.001f * distance * distance));
}

t_color	calc_specular_color(t_specular_params params, float specular_power,
		float light_intensity)
{
	t_color		specular;
	t_vector	reflection;
	float		spec_intensity;
	float		dot_ln;
	float		dot_rv;

	dot_ln = vector_dot_product(params.normal, params.light_dir);
	reflection = vector_subtraction(
			scalars_mult_by_vectors(2.0f * dot_ln, params.normal),
			params.light_dir);
	reflection = vectors_unit(reflection);
	dot_rv = vector_dot_product(reflection, params.view_dir);
	if (dot_rv < 0.0f)
		dot_rv = 0.0f;
	spec_intensity = powf(dot_rv, specular_power) * light_intensity;
	specular.r = (int)(params.light_color.r * spec_intensity);
	specular.g = (int)(params.light_color.g * spec_intensity);
	specular.b = (int)(params.light_color.b * spec_intensity);
	return (specular);
}

t_color	calculate_specular_component(t_minirt *mini,
		t_intersection *intersection, t_light *light)
{
	t_specular_params	spec_params;

	spec_params = (t_specular_params){
		vectors_unit(light_dir_helper(light, intersection)),
		intersection->normal,
		vectors_unit(scalars_mult_by_vectors(-1.0f, mini->ray.direction)),
		light->colors
	};
	return (calc_specular_color(spec_params, intersection->specular,
			light->ratio));
}
