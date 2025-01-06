/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 03:54:09 by aahadji           #+#    #+#             */
/*   Updated: 2025/01/06 15:31:53 by aahadji          ###   ########.fr       */
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
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*temp;
	int		size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
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

int	no_n_end(char **str, int fd)
{
	char	*temp;
	char	*new_str;
	int		bytes_read;

	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp)
		return (0);
	bytes_read = read(fd, temp, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(temp);
		return (0);
	}
	temp[bytes_read] = '\0';
	new_str = ft_strjoin(*str, temp);
	free(*str);
	*str = new_str;
	free(temp);
	return (1);
}

int	eol_position(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}