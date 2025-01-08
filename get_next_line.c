/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 03:32:42 by aahadji           #+#    #+#             */
/*   Updated: 2025/01/08 18:51:08 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	next_line[BUFFER_SIZE * 2 + 2] = "\0";
	char		*line;
	char		*temp;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = ft_calloc(BUFFER_SIZE + 2, sizeof(char));
	if (!line)
		return (NULL);
	if (read(fd, line, BUFFER_SIZE) <= 0)
	{
		free(line);
		return (NULL);
	}
	temp = start_gnl(next_line, line, fd);
	return (temp);
}

char	*start_gnl(char *next_line, char *line, int fd)
{
	char	*str;

	str = ft_strjoin(next_line, line);
	if (!str)
		return (NULL);
	free(line);
	while (eol_position(str) == -1)
	{
		if (no_n_end(&str, fd) == 1)
			continue ;
		else
		{
			next_line = NULL;
			free(str);
			return (NULL);
		}
	}
	return (line_finish(str, next_line));
}

char	*line_finish(char *str, char *next_line)
{
	int		pos;
	int		i;
	char	*line;

	pos = eol_position(str);
	if (pos == -1)
	{
		ft_strlcpy(next_line, "", BUFFER_SIZE * 2 + 2);
		return (str);
	}
	line = ft_calloc(pos + 2, sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, str, pos + 2);
	i = 0;
	i = ft_strlcpy(next_line, str + pos + 1, BUFFER_SIZE * 2 + 2);
	next_line[i] = '\0';
	free(str);
	return (line);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*#include <stdio.h>

int	main(void)
{
	int fd = open("test", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	for (int i = 0; i < 18; ++i)
	{
	}
	char *temp;
	while ((temp = get_next_line(fd)))
	{
		printf("===========\n");
		printf("%s", temp);
		free(temp);
	}
	close(fd);
	return (0);
}*/