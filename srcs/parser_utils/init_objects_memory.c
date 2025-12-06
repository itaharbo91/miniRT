/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects_memory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:45:37 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/16 21:53:33 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include <fcntl.h>

static void	count_helpers(char *line, t_minirt *mini)
{
	int	i;

	i = 0;
	skip_spaces(line, &i);
	if (ft_strncmp(&line[i], "A ", 2) == 0)
		mini->scene.ambi_light_count++;
	else if (ft_strncmp(&line[i], "C ", 2) == 0)
		mini->scene.camera_count++;
	else if (ft_strncmp(&line[i], "L ", 2) == 0)
		mini->scene.light_count++;
	else if (ft_strncmp(&line[i], "sp ", 3) == 0)
		mini->scene.sphere_count++;
	else if (ft_strncmp(&line[i], "pl ", 3) == 0)
		mini->scene.plane_count++;
	else if (ft_strncmp(&line[i], "cy ", 3) == 0)
		mini->scene.cylinder_count++;
	if (ft_strncmp(&line[i], "sp ", 3) == 0
		&& ft_strncmp(&line[i], "pl ", 3) == 0
		&& ft_strncmp(&line[i], "cy ", 3) == 0)
		mini->scene.object_count++;
}

static void	read_line(t_minirt *mini, int fd)
{
	char	*line;
	int		i;
	int		non_empty_line;

	non_empty_line = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i = 0;
		while (ft_isspace(line[i]) || line[i] == '\n')
			i++;
		if (line[i] == '\0')
		{
			free(line);
			continue ;
		}
		else
			non_empty_line++;
		count_helpers(&line[i], mini);
		free(line);
	}
	if (non_empty_line == 0)
		fatal_err("Scene file is empty or contains only whitespace!", mini);
}

void	count_objects(char *file, t_minirt *mini)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		fatal_perror("count_objects: open", mini);
	mini->scene.object_count = 0;
	read_line(mini, fd);
	close(fd);
}

void	elements_count_error(t_minirt *mini)
{
	if (mini->scene.ambi_light_count > 1)
		fatal_err("Too many ambient light!", mini);
	if (mini->scene.camera_count > 1)
		fatal_err("Too many cameras!", mini);
	if (mini->scene.light_count > 1)
		fatal_err("Too many lights!", mini);
	if (mini->scene.ambi_light_count < 1)
		fatal_err("No ambient light!", mini);
	if (mini->scene.camera_count < 1)
		fatal_err("No camera!", mini);
	if (mini->scene.light_count < 1)
		fatal_err("No light!", mini);
}

void	init_objects_memory(t_minirt *mini)
{
	mini->scene.spheres = ft_calloc(sizeof(t_sphere),
			mini->scene.sphere_count);
	if (!mini->scene.spheres)
		fatal_perror("init_object_memory: malloc spheres", mini);
	mini->scene.planes = ft_calloc(sizeof(t_plane),
			mini->scene.plane_count);
	if (!mini->scene.planes)
		fatal_perror("init_object_memory: malloc planes", mini);
	mini->scene.cylinders = ft_calloc(sizeof(t_cylinder),
			mini->scene.cylinder_count);
	if (!mini->scene.cylinders)
		fatal_perror("init_object_memory: malloc cylinders", mini);
	mini->scene.sphere_count = 0;
	mini->scene.plane_count = 0;
	mini->scene.cylinder_count = 0;
}
