/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:21:50 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 19:29:03 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	m_rotate_x(t_matrix *matrix, float angle)
{
	init_matrix(matrix);
	matrix->m[1][1] = cos(angle);
	matrix->m[1][2] = -sin(angle);
	matrix->m[2][1] = sin(angle);
	matrix->m[2][2] = cos(angle);
}

void	m_rotate_y(t_matrix *matrix, float angle)
{
	init_matrix(matrix);
	matrix->m[0][0] = cos(angle);
	matrix->m[0][2] = sin(angle);
	matrix->m[2][0] = -sin(angle);
	matrix->m[2][2] = cos(angle);
}

void	m_rotate_z(t_matrix *matrix, float angle)
{
	init_matrix(matrix);
	matrix->m[0][0] = cos(angle);
	matrix->m[0][1] = -sin(angle);
	matrix->m[1][0] = sin(angle);
	matrix->m[1][1] = cos(angle);
}
