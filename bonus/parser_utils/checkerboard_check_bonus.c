/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:54:35 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/20 19:28:04 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	checkerboard_check(char val, bool *checkerboard, t_minirt *mini)
{
	if (val == '1')
		*checkerboard = true;
	else if (val == '0')
		*checkerboard = false;
	else
		fatal_err("Invalid checkerboard value, must be 1 for ON, 0 for OFF!",
			mini);
}
