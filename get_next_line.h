/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:14:39 by aahadji           #+#    #+#             */
/*   Updated: 2025/01/06 11:36:53 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*start_gnl(char *next_line, char *line, int fd);
void	no_n_end(char *str, int fd);
void	*ft_calloc(size_t count, size_t size);
char	*line_finish(char *str, char *next_line);
char	*ft_strjoin(const char *s1, const char *s2);
int		eol_position(char *line);
#endif