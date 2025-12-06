/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:22:59 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/17 18:06:06 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	init_intersections(t_minirt *mini, t_ray *ray)
{
	int	total_objects;

	total_objects = mini->scene.sphere_count + mini->scene.plane_count
		+ mini->scene.cylinder_count;
	if (total_objects == 0)
		total_objects = 10;
	total_objects = total_objects * 2 + 10;
	ray->intersections
		= malloc(sizeof(t_intersection) * total_objects);
	if (!ray->intersections)
		fatal_perror("init_intersections: malloc", mini);
	ray->intersection_count = 0;
}

static void	put_pixel_to_img(t_img *img, int x, int y, t_color color)
{
	int	pix;
	int	color_int;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pix = (y * img->size_line) + (x * (img->bpp / 8));
	if (pix < 0 || pix >= img->width * img->height * (img->bpp / 8))
		return ;
	color = clamp_color(color);
	color_int = (color.r << 16) | (color.g << 8) | color.b;
	*(int *)(img->data + pix) = color_int;
}

static void	rendering(t_minirt *mini, int i, int j)
{
	t_intersection	*closest_inters;
	t_color			final_color;

	mini->ray.intersection_count = 0;
	generate_ray(mini, i, j);
	sphere_intersections(mini, &mini->ray);
	plane_intersections(mini, &mini->ray);
	cylinder_intersections(mini, &mini->ray);
	closest_inters = get_closet_intersection(mini, &mini->ray);
	if (closest_inters == NULL)
	{
		final_color.r = 0;
		final_color.g = 0;
		final_color.b = 0;
	}
	else
		final_color = final_color_pixel(mini, closest_inters);
	put_pixel_to_img(&mini->data.img, i, j, final_color);
}

void	render_ray(t_minirt *mini)
{
	int				i;
	int				j;

	camera_cues(mini);
	viewport(mini);
	init_intersections(mini, &mini->ray);
	init_intersections(mini, &mini->shadow_ray);
	i = 0;
	while (i < mini->data.img.width)
	{
		j = 0;
		while (j < mini->data.img.height)
		{
			rendering(mini, i, j);
			j++;
		}
		i++;
	}
	free(mini->ray.intersections);
	free(mini->shadow_ray.intersections);
}
