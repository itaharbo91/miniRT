/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_struct_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:43:57 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/22 17:33:01 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_BONUS_H
# define MINIRT_STRUCT_BONUS_H

# include "minirt_scene_bonus.h"
# include "minirt_ray_bonus.h"

typedef enum e_mode
{
	MODE_CAMERA,
	MODE_SPHERE,
	MODE_CYLINDER,
	MODE_PLANE,
	MODE_CONE,
	MODE_LIGHT
}	t_mode;

typedef struct s_light_params
{
	t_color	light_color;
	float	intensity;
	float	ratio;
	float	attenuation;
}	t_light_params;

typedef struct s_specular_params
{
	t_vector	light_dir;
	t_vector	normal;
	t_vector	view_dir;
	t_color		light_color;
}	t_specular_params;

typedef struct s_matrix
{
	float		m[4][4];
}	t_matrix;

typedef struct s_transform_point
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_transform_point;

typedef struct s_cmd
{
	t_matrix	rot_matrix;
	t_mode		mode;
	int			selected_sphere;
	int			selected_cylinder;
	int			selected_plane;
	int			selected_cone;
	int			selected_light;
}	t_cmd;

typedef struct s_img
{
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;

typedef struct s_minirt
{
	t_scene	scene;
	t_ray	ray;
	t_ray	shadow_ray;
	t_data	data;
	t_cmd	cmd;
	char	*current_line;
	int		current_fd;
}	t_minirt;

#endif
