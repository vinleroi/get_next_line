/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 03:32:42 by aahadji           #+#    #+#             */
/*   Updated: 2025/01/06 15:23:38 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	next_line[BUFFER_SIZE + 1] = "\0";
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	// printf("%s\n", next_line);
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (NULL);
	if (read(fd, line, BUFFER_SIZE) <= 0)
	{
		free(line);
		return (NULL);
	}
	return (start_gnl(next_line, line, fd));
}

char	*start_gnl(char *next_line, char *line, int fd)
{
	char	*str;

	str = ft_strjoin(next_line, line);
	if (!str)
		return (NULL);
	free(line);
	while (eol_position(str) == -1 && no_n_end(&str, fd) == 1)
	{
	}
	return (line_finish(str, next_line));
}
char	*line_finish(char *str, char *next_line)
{
	int pos;
	int i;

	pos = eol_position(str) + 1;
	i = 0;
	while (str[pos])
	{
		if (str[pos])
		{
			next_line[i] = str[pos];
			str[pos] = '\0';
		}
		else
			next_line[i] = '\0';
		pos++;
		i++;
	}
	while (i < BUFFER_SIZE)
	{
		next_line[i] = '\0';
		i++;
	}
	return (str);
}