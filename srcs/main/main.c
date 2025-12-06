/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:30:57 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/17 21:23:42 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_cmd(t_cmd *cmd)
{
	cmd->mode = 0;
	cmd->selected_sphere = 0;
	cmd->selected_cylinder = 0;
	cmd->selected_plane = 0;
	cmd->selected_light = 0;
	init_matrix(&cmd->rot_matrix);
}

void	render_minirt(t_minirt *mini)
{
	render_ray(mini);
	mlx_put_image_to_window(mini->data.mlx_ptr,
		mini->data.win_ptr, mini->data.img.img, 0, 0);
	controls_info_box(mini);
}

static int	expose_hook(t_minirt *mini)
{
	mlx_put_image_to_window(mini->data.mlx_ptr,
		mini->data.win_ptr, mini->data.img.img, 0, 0);
	controls_info_box(mini);
	return (0);
}

int	main(int ac, char **av)
{
	t_minirt	*mini;

	if (ac != 2)
		return (err_msg("Usage: ./miniRT [file.rt]"), 1);
	mini = ft_calloc(1, sizeof(t_minirt));
	if (!mini)
		return (fatal_perror("main: malloc", NULL), 1);
	parser_file(av[1], mini);
	init_cmd(&mini->cmd);
	init_window_and_img(mini, 1200, 900);
	render_minirt(mini);
	mlx_hook(mini->data.win_ptr, 2, 1L << 0, key_press, mini);
	mlx_hook(mini->data.win_ptr, 3, 1L << 1, key_release, mini);
	mlx_hook(mini->data.win_ptr, 17, 0, close_hook, mini);
	mlx_hook(mini->data.win_ptr, 12, 1L << 15, expose_hook, mini);
	mlx_loop(mini->data.mlx_ptr);
	free_minirt(mini);
	return (EXIT_SUCCESS);
}
