/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:57:52 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/16 17:10:58 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_transform_point	point_to_transform_point(t_point p)
{
	t_transform_point	tp;

	tp.x = p.x;
	tp.y = p.y;
	tp.z = p.z;
	tp.w = 1.0f;
	return (tp);
}

t_point	transform_point_to_point(t_transform_point tp)
{
	t_point	p;

	p.x = tp.x;
	p.y = tp.y;
	p.z = tp.z;
	return (p);
}

void	init_matrix(t_matrix *matrix)
{
	ft_bzero(matrix->m, sizeof(matrix->m));
	matrix->m[0][0] = 1;
	matrix->m[1][1] = 1;
	matrix->m[2][2] = 1;
	matrix->m[3][3] = 1;
}

void	multiply_matrix(t_matrix *result, t_matrix *other)
{
	int			i;
	int			j;
	int			k;
	t_matrix	tmp;

	init_matrix(&tmp);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			tmp.m[i][j] = 0;
			k = 0;
			while (k < 4)
			{
				tmp.m[i][j] += result->m[i][k] * other->m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	*result = tmp;
}

void	matrix_to_point(t_matrix *matrix, t_transform_point *point)
{
	float	tmp_x;
	float	tmp_y;
	float	tmp_z;
	float	tmp_w;

	tmp_x = point->x;
	tmp_y = point->y;
	tmp_z = point->z;
	tmp_w = point->w;
	tmp_x = matrix->m[0][0] * point->x + matrix->m[0][1] * point->y
		+ matrix->m[0][2] * point->z + matrix->m[0][3] * point->w;
	tmp_y = matrix->m[1][0] * point->x + matrix->m[1][1] * point->y
		+ matrix->m[1][2] * point->z + matrix->m[1][3] * point->w;
	tmp_z = matrix->m[2][0] * point->x + matrix->m[2][1] * point->y
		+ matrix->m[2][2] * point->z + matrix->m[2][3] * point->w;
	tmp_w = matrix->m[3][0] * point->x + matrix->m[3][1] * point->y
		+ matrix->m[3][2] * point->z + matrix->m[3][3] * point->w;
	point->x = tmp_x;
	point->y = tmp_y;
	point->z = tmp_z;
	point->w = tmp_w;
}
