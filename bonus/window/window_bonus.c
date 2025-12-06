/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:58:05 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 19:14:42 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	init_window(t_minirt *mini)
{
	mini->data.mlx_ptr = mlx_init();
	if (!mini->data.mlx_ptr)
		fatal_perror("init_window: mlx_init", mini);
	mini->data.win_ptr = mlx_new_window(mini->data.mlx_ptr,
			mini->data.img.width, mini->data.img.height, "miniRT");
	if (!mini->data.win_ptr)
		fatal_perror("init_window: mlx_new_window", mini);
}

static void	init_img(t_minirt *mini)
{
	mini->data.img.img = mlx_new_image(mini->data.mlx_ptr,
			mini->data.img.width, mini->data.img.height);
	if (!mini->data.img.img)
		fatal_perror("init_img: mlx_new_image", mini);
	mini->data.img.data = mlx_get_data_addr(mini->data.img.img,
			&mini->data.img.bpp, &mini->data.img.size_line,
			&mini->data.img.endian);
	if (!mini->data.img.data)
		fatal_perror("init_img: mlx_get_data_addr", mini);
}

void	init_window_and_img(t_minirt *mini, int width, int height)
{
	mini->data.img.width = width;
	mini->data.img.height = height;
	init_window(mini);
	init_img(mini);
}
