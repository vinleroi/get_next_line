/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 03:32:42 by aahadji           #+#    #+#             */
/*   Updated: 2025/01/06 11:34:21 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*next_line = NULL;
	char		*line;
	int			len;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!next_line)
		return (NULL);
	if (read(fd, &line, BUFFER_SIZE) <= 0)
		return (NULL);
	if (line[0] == '\0')
	{
		free(next_line);
		next_line = NULL;
		free(line);
		return (NULL);
	}
	return (start_gnl(next_line, line, fd));
}

char	*start_gnl(char *next_line, char *line, int fd)
{
	char	*str;

	str = ft_strjoin(next_line, line);
	while (eol_position(str) == -1)
		no_n_end(str, fd);
	return (line_finish(str, next_line));
}
