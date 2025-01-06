/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 03:54:09 by aahadji           #+#    #+#             */
/*   Updated: 2025/01/06 11:34:41 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*temp;
	size_t			total_size;
	size_t			i;

	total_size = count * size;
	if (size != 0 && total_size / size != count)
		return (NULL);
	temp = (unsigned char *)malloc(total_size);
	if (!temp)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		temp[i] = '\0';
		i++;
	}
	return ((void *)temp);
}
char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*temp;
	int		size;

	size = ft_strlen(s1) + ft_strlen(s2);
	temp = (char *)malloc(sizeof(char) * size + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		temp[i] = s2[j];
		i++;
		j++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*line_finish(char *str, char *next_line)
{
	int	pos;
	int	i;

	pos = eol_position(str) + 1;
	i = 0;
	while (str[pos] || next_line[i])
	{
		if (str[pos])
		{
			next_line[i] = str[pos];
			str[pos] = '\0';
		}
		next_line[i] = '\0';
		pos++;
		i++;
	}
	return (str);
}
void	no_n_end(char *str, int fd)
{
	char	*temp;

	temp = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!temp)
		return (NULL);
	if (read(fd, &temp, BUFFER_SIZE) <= 0)
		return (NULL);
	str = ft_strjoin(str, temp);
	free(temp);
}

int	eol_position(char *line)
{
	int i;

	while (line[i])
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}