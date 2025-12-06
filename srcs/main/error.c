/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:28:43 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/17 18:14:09 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	err_msg(char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

// It prints an error message to stderr using perror,
// which includes the system error message.
void	fatal_perror(char *msg, t_minirt *mini)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	perror(msg);
	if (mini)
		free_minirt(mini);
	exit(EXIT_FAILURE);
}

// It prints an error message to stderr and then exits the program.
void	fatal_err(char *msg, t_minirt *mini)
{
	err_msg(msg);
	if (mini)
		free_minirt(mini);
	exit(EXIT_FAILURE);
}
