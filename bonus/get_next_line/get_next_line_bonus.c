/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:53:11 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 19:03:54 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_file(int fd, char *tmp)
{
	char	*buff;
	int		read_byte;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
	{
		free(tmp);
		return (NULL);
	}
	read_byte = 1;
	while (read_byte > 0 && !ft_strchr(tmp, '\n'))
	{
		read_byte = read(fd, buff, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buff);
			free(tmp);
			return (NULL);
		}
		buff[read_byte] = '\0';
		tmp = ft_strjoin(tmp, buff);
	}
	free(buff);
	return (tmp);
}

char	*ft_extract(char *tmp)
{
	int		i;
	char	*line;

	i = 0;
	if (!tmp[i])
		return (NULL);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		line[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\n')
		line[i] = tmp[i];
	if (tmp[i] == '\n')
		i++;
	line[i] = '\0';
	return (line);
}

char	*ft_next_line(char *tmp)
{
	int		i;
	int		j;
	char	*next_line;

	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (!tmp[i])
	{
		free(tmp);
		return (NULL);
	}
	next_line = malloc(sizeof(char) * (ft_strlen(tmp) - i + 1));
	if (!next_line)
	{
		free(tmp);
		return (NULL);
	}
	i++;
	j = 0;
	while (tmp[i])
		next_line[j++] = tmp[i++];
	next_line[j] = '\0';
	free(tmp);
	return (next_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*tmp = NULL;

	if (fd == -42)
	{
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = ft_read_file(fd, tmp);
	if (!tmp)
		return (NULL);
	line = ft_extract(tmp);
	if (!line)
		return (free(tmp), tmp = NULL, NULL);
	tmp = ft_next_line(tmp);
	return (line);
}

void	cleanup_get_next_line(void)
{
	get_next_line(-42);
}
/*
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;
    int i = 0;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Erreur d'ouverture du fichier");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        i++;
        free(line);
    }
    if (line == NULL)
    {
        printf("Fin du fichier ou erreur de lecture.\n");
    }
    printf("%d\n", i);
    close(fd);
    return (0);
}*/
