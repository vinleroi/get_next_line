/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 03:32:42 by aahadji           #+#    #+#             */
/*   Updated: 2025/01/30 17:45:10 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	next_line[BUFFER_SIZE * 2 + 1] = "\0";
	char		*line;
	char		*temp;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (NULL);
	if (read(fd, line, BUFFER_SIZE) <= 0 && next_line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	temp = start_gnl(next_line, line, &fd);
	return (temp);
}

char	*start_gnl(char *next_line, char *line, int *fd)
{
	char	*str;

	str = ft_strjoin(next_line, line);
	if (!str)
		return (NULL);
	free(line);
	if (no_n_end(&str, fd) != 1)
	{
		free(str);
		return (NULL);
	}
	return (line_finish(str, next_line));
}

char	*line_finish(char *str, char *next_line)
{
	int		pos;
	char	*line;
	int		i;

	pos = eol_position(str);
	i = 0;
	if (pos == -1)
		return (NULL);
	else if (pos == -2)
		return (free(str), endof_file(next_line));
	line = ft_calloc(pos + 2, sizeof(char));
	if (!line)
		return (free(str), NULL);
	ft_strlcpy(line, str, pos + 2);
	while ((pos + 1 + i) <= (BUFFER_SIZE * 2) && str[pos + 1 + i])
	{
		next_line[i] = str[pos + 1 + i];
		i++;
	}
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

char	*endof_file(char *next_line)
{
	int		pos;
	char	*line;
	int		i;

	pos = eol_position(next_line);
	if (pos >= 0)
	{
		line = ft_calloc(pos + 2, sizeof(char));
		if (!line)
			return (NULL);
		ft_strlcpy(line, next_line, pos + 2);
		i = 0;
		while (next_line[pos + 1 + i])
		{
			next_line[i] = next_line[pos + 1 + i];
			i++;
		}
		next_line[i] = '\0';
		return (line);
	}
	return (NULL);
}
// int	main(void)
// {
// 	int fd = open("test2", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	char *temp;
// 	int i = 0;
// 	int j = 0;
// 	while ((temp = get_next_line(fd)))
// 	{
// 		j = ft_strlen(temp);
// 		printf("ligne : %i ===========\n", i);
// 		printf("%s \n", temp);
// 		printf("there was  %i  letters ===========\n \n", j);
// 		free(temp);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }