/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:16:43 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/17 18:21:04 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static void	id_check(char *id, t_minirt *mini)
{
	if ((ft_strcmp(id, "A") != 0) && (ft_strcmp(id, "C") != 0)
		&& (ft_strcmp(id, "L") != 0) && (ft_strcmp(id, "sp") != 0)
		&& (ft_strcmp(id, "pl") != 0) && (ft_strcmp(id, "cy") != 0))
		fatal_err("Unknown identifier!", mini);
}

static void	parsing_dispatch(char *line, t_minirt *mini, char *id)
{
	if (ft_strcmp(id, "A") == 0)
		parse_ambi_light(line, mini);
	else if (ft_strcmp(id, "C") == 0)
		parse_camera(line, mini);
	else if (ft_strcmp(id, "L") == 0)
		parse_light(line, mini);
	else if (ft_strcmp(id, "sp") == 0)
		parse_sphere(line, mini);
	else if (ft_strcmp(id, "pl") == 0)
		parse_plane(line, mini);
	else if (ft_strcmp(id, "cy") == 0)
		parse_cylinder(line, mini);
	else
		fatal_err("Unknown element in scene!", mini);
}

static void	parse_line(char *line, t_minirt *mini)
{
	int		i;
	char	id[3];

	mini->current_line = line;
	id[0] = 0;
	id[1] = 0;
	id[2] = 0;
	i = 0;
	skip_spaces(line, &i);
	id[0] = line[i];
	if (ft_isalpha(line[i]) && !ft_isalpha(line[i + 1]))
		id[1] = '\0';
	else
	{
		id[1] = line[i + 1];
		id[2] = '\0';
		if (!ft_isspace(line[i + 2]))
			fatal_err("Invalid identifier in scene!", mini);
	}
	id_check(id, mini);
	parsing_dispatch(&line[i], mini, id);
	mini->current_line = NULL;
}

static void	init_scene(t_minirt *mini, int fd)
{
	char	*line;
	int		i;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			cleanup_get_next_line();
			break ;
		}
		i = 0;
		while (ft_isspace(line[i]) || line[i] == '\n')
			i++;
		if (line[i] == '\0')
		{
			free(line);
			continue ;
		}
		parse_line(line, mini);
		free(line);
	}
}

void	parser_file(char *file, t_minirt *mini)
{
	int	fd;
	int	i;

	mini->current_fd = -1;
	i = 0;
	while (file[i] && file[i] != '.')
		i++;
	if (file[i] == '\0' || file[i + 1] != 'r'
		|| file[i + 2] != 't' || file[i + 3] != '\0')
		fatal_err("Invalid file extension! Expected .rt", mini);
	count_objects(file, mini);
	elements_count_error(mini);
	init_objects_memory(mini);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		fatal_perror("parser_file: open", mini);
	mini->current_fd = fd;
	init_scene(mini, fd);
	mini->current_fd = -1;
	close(fd);
}
