/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:26:39 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/29 14:29:50 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

# define EPSILON 1.0e-6
# define BIAS 1e-3
# define M_PI 3.14159265358979323846

# include "minirt_struct_bonus.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <mlx.h>

//Parser
void				parser_file(char *file, t_minirt *mini);
void				parse_ambi_light(char *line, t_minirt *mini);
void				parse_camera(char *line, t_minirt *mini);
void				parse_light(char *line, t_minirt *mini);
void				parse_sphere(char *line, t_minirt *mini);
void				parse_plane(char *line, t_minirt *mini);
void				parse_cylinder(char *line, t_minirt *mini);
void				count_objects(char *file, t_minirt *mini);
void				elements_count_error(t_minirt *mini);
void				init_objects_memory(t_minirt *mini);

//Parser utils
int					ratio_conv(char *line, t_minirt *mini, float *dst, int *i);
void				point_conv(char *line, t_minirt *mini, t_point *dst,
						int *i);
int					vector_conv(char *line, t_minirt *mini, t_vector *dst,
						int *i);
int					fov_conv(char *line, t_minirt *mini, int *i);
int					color_parse(char *line, t_minirt *mini, t_color *dst,
						int *i);
int					diameter_conv(char *line, t_minirt *mini, float *dst,
						int *i);
int					height_conv(char *line, t_minirt *mini, float *dst,
						int *i);

//Error handling and cleaning
void				err_msg(char *msg);
void				free_minirt(t_minirt *mini);
void				fatal_err(char *msg, t_minirt *mini);
void				fatal_perror(char *msg, t_minirt *mini);

//Utils
void				ft_putstr_fd(char *str, int fd);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(char *s1, char *s2);
void				skip_spaces(char *line, int *i);
void				ft_bzero(void *s, size_t n);
long long			ft_atoi(const char *nptr);
float				ft_strtof(const char *theString, char **end);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isspace(int c);

//Colors
t_color				color_transfer(t_color color);
t_color				color_addition(t_color a, t_color b);
t_color				color_multiplication(t_color a, float factor);
t_color				final_color_pixel(t_minirt *mini,
						t_intersection *intersection);
t_color				clamp_color(t_color color);
t_vector			light_dir_helper(t_light *light,
						t_intersection *intersection);
bool				is_in_shadow_for_light(t_minirt *mini,
						t_intersection *intersection, t_light *light);
float				attenuation_helper(float distance);

//Math calculations
t_vector			vector_calculate(t_point a, t_point b);
t_vector			vector_addition(t_vector a, t_vector b);
t_vector			vector_subtraction(t_vector a, t_vector b);
t_vector			vector_division(t_vector a, t_vector b);
t_vector			scalars_mult_by_vectors(float u, t_vector a);
float				vector_magnitude(t_vector a);
t_vector			vectors_unit(t_vector a);
float				vector_dot_product(t_vector a, t_vector b);
t_vector			vector_cross_products(t_vector a, t_vector b);
t_vector			point_to_vector(t_point p);
t_point				vector_to_point(t_vector v);

// Sphere equations
t_vector			sp_param_ray_equa(t_vector origin, float u,
						t_vector direction);
float				sp_surface_equation(t_vector origin, float u,
						t_vector direction, t_vector center);
t_point				sp_surf_inters_delta(t_vector direction,
						t_vector origin, t_vector center, float r);
float				sp_ray_surf_inters(t_vector origin, t_vector direction,
						t_vector center, float r);
t_vector			sp_surf_normal_vector(t_vector direction, t_vector origin,
						t_vector center, float u);

// Cylinder equations
t_vector			cap_normal_vector(t_ray *ray, t_cylinder *cylinder,
						t_vector cap);
int					check_cylinder_height(t_vector point, t_vector center,
						t_vector axis, float height);
t_vector			cy_surf_normal_vector(t_vector point, t_vector center,
						t_vector axis);

// Ray intersections
void				init_intersections(t_minirt *mini, t_ray *ray);
void				sphere_intersections(t_minirt *mini, t_ray *ray);
void				plane_intersections(t_minirt *mini, t_ray *ray);
void				cylinder_intersections(t_minirt *mini, t_ray *ray);

// Rendering
void				render_ray(t_minirt *mini);
void				generate_ray(t_minirt *mini, int i, int j);
void				camera_cues(t_minirt *mini);
void				viewport(t_minirt *mini);
t_intersection		*get_closet_intersection(t_minirt *mini, t_ray *ray);
void				generate_ray(t_minirt *mini, int i, int j);

// Events and Controls
int					key_hook(int keycode, t_minirt *mini);
int					key_press(int key, t_minirt *mini);
int					key_release(int key, t_minirt *mini);
int					close_hook(void *params);
void				handle_translation(int key, t_minirt *mini);
void				handle_rotation(int key, t_minirt *mini);
void				handle_mode_selection(int key, t_minirt *mini);
void				handle_object_selection(int key, t_minirt *mini);
void				render_minirt(t_minirt *mini);
void				light_translation(t_minirt *mini, int key, float delta);

// Object Transformations
void				cycle_object_forward(t_minirt *mini);
void				cycle_object_backward(t_minirt *mini);
void				apply_object_translation(int key, t_minirt *mini,
						float delta);
void				apply_object_rotation(int key, t_minirt *mini, float angle);
void				apply_object_resize(int key, t_minirt *mini);

// Matrix calculations
void				multiply_matrix(t_matrix *result, t_matrix *other);
void				init_matrix(t_matrix *matrix);
void				m_rotate_x(t_matrix *matrix, float angle);
void				m_rotate_y(t_matrix *matrix, float angle);
void				m_rotate_z(t_matrix *matrix, float angle);
void				matrix_to_point(t_matrix *matrix, t_transform_point *point);
t_transform_point	point_to_transform_point(t_point p);
t_point				transform_point_to_point(t_transform_point tp);

// Window and Image
void				init_window_and_img(t_minirt *mini, int width, int height);
void				controls_info_box(t_minirt *mini);

// Specular
int					specular_conv(char *line, t_minirt *mini, float *dst,
						int *i);
t_color				calculate_specular_component(t_minirt *mini,
						t_intersection *intersection, t_light *light);
t_color				calc_specular_color(t_specular_params params,
						float specular_power, float light_intensity);

// Checkerboard
void				checkerboard_check(char val, bool *checkerboard,
						t_minirt *mini);
t_color				get_object_color(t_intersection *intersection);
t_color				cylinder_checkerboard_cap(float h, t_vector axis,
						t_vector rel, float radius);
t_color				cylinder_checkerboard_around(t_cylinder *cyl, t_vector rel,
						t_vector u_axis, t_vector v_axis);
t_color				cone_checkerboard_cap(t_cone *cone, t_vector radial_vec,
						t_vector axis, t_vector ref);
t_color				cone_checkerboard_around(t_cone *cone, t_vector radial_vec,
						float height, t_vector ref);

// Cone
void				parse_cone(char *line, t_minirt *mini);
bool				check_cone_height(t_vector point, t_cone *cone);
float				vector_length(t_vector v);
t_vector			cone_normal_vector(t_vector point, t_cone *cone);
float				a_discriminant(t_ray *ray, t_cone *cone);
float				b_discriminant(t_ray *ray, t_cone *cone);
float				c_discriminant(t_ray *ray, t_cone *cone);
void				t_choose_fill(t_ray *ray, t_cone *cone, float t);
void				cone_fill(t_ray *ray, t_cone *cone, float u);
void				cone_intersections(t_minirt *mini, t_ray *ray);

#endif
