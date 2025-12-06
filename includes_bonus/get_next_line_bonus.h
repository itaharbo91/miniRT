/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:46:32 by itaharbo          #+#    #+#             */
/*   Updated: 2025/08/18 18:11:54 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_extract(char *tmp);
char	*ft_read_file(int fd, char *tmp);
char	*ft_next_line(char *tmp);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(char *str);
void	cleanup_get_next_line(void);

#endif
