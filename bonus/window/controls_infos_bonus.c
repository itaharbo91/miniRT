/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_infos_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:24:22 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/22 20:07:28 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	controls_info_box_helper(t_minirt *mini)
{
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, 10, 15, 0x87CEEB,
		"Camera: 1");
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, 10, 30, 0x87CEEB,
		"Spheres: 2");
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, 10, 45, 0x87CEEB,
		"Cylinders: 3");
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, 10, 60, 0x87CEEB,
		"Planes: 4");
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, 10, 75, 0x87CEEB,
		"Cones: 5");
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, 10, 90, 0x87CEEB,
		"Lights: 6");
}

void	controls_info_box(t_minirt *mini)
{
	controls_info_box_helper(mini);
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, 10, 115, 0xC0C0C0,
		"Next Object: TAB");
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, 10, 140, 0xC0C0C0,
		"Move: Arrows");
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, 10, 155, 0xC0C0C0,
		"Forward/Back: X/Z");
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, 10, 180, 0xC0C0C0,
		"Rotate: W/S/A/D");
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, 10, 195, 0xC0C0C0,
		"Z-Rotate: Q/E");
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, 10, 220, 0xC0C0C0,
		"Resize: +/-");
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, 10, 235, 0xC0C0C0,
		"Height: N/M");
	mlx_string_put(mini->data.mlx_ptr, mini->data.win_ptr, mini->data.img.width
		- 60, 15, 0x8B0000, "Exit: ESC");
}
