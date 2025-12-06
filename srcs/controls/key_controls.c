/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:47:40 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 19:55:42 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define ESC 65307
#define UP 65362
#define DOWN 65364
#define LEFT 65361
#define RIGHT 65363
#define INCREASE 65451
#define DECREASE 65453
#define INCREASE_HEIGHT 110
#define DECREASE_HEIGHT 109
#define ROTATE_UP 119
#define ROTATE_DOWN 115
#define ROTATE_LEFT 97
#define ROTATE_RIGHT 100
#define ROTATE_Z_LEFT 113
#define ROTATE_Z_RIGHT 101
#define FORWARD 120
#define BACKWARD 122
#define CTRL 65507

#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define TAB 65289
#define SHIFT_TAB 65056

int	key_hook(int key, t_minirt *mini)
{
	if (key == ESC)
	{
		free_minirt(mini);
		exit(EXIT_SUCCESS);
	}
	else if (key == KEY_1 || key == KEY_2 || key == KEY_3
		|| key == KEY_4 || key == KEY_5)
		handle_mode_selection(key, mini);
	else if (key == TAB || key == SHIFT_TAB)
		handle_object_selection(key, mini);
	else if (key == UP || key == DOWN || key == LEFT || key == RIGHT
		|| key == FORWARD || key == BACKWARD)
		handle_translation(key, mini);
	else if (key == ROTATE_UP || key == ROTATE_DOWN
		|| key == ROTATE_LEFT || key == ROTATE_RIGHT
		|| key == ROTATE_Z_LEFT || key == ROTATE_Z_RIGHT)
		handle_rotation(key, mini);
	else if (key == INCREASE || key == DECREASE || key == INCREASE_HEIGHT
		|| key == DECREASE_HEIGHT)
		apply_object_resize(key, mini);
	render_minirt(mini);
	return (0);
}

int	key_press(int key, t_minirt *mini)
{
	key_hook(key, mini);
	return (0);
}

int	key_release(int key, t_minirt *mini)
{
	(void)key;
	(void)mini;
	return (0);
}

int	close_hook(void *params)
{
	t_minirt	*mini;

	mini = (t_minirt *)params;
	free_minirt(mini);
	exit(EXIT_SUCCESS);
}
