/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 03:32:42 by aahadji           #+#    #+#             */
/*   Updated: 2025/01/31 18:11:46 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	update_nl(char *nl)
{
	size_t	r;
	size_t	w;

	r = 0;
	while (nl[r] && nl[r] != '\n')
		++r;
	if (nl[r])
		++r;
	w = 0;
	while (nl[r])
		nl[w++] = nl[r++];
	while (nl[w])
		nl[w++] = '\0';
}

static char	*gnfree(char *dest)
{
	free(dest);
	return (NULL);
}

static char	*gnl_copy(char *src, long fd, char *buffer)
{
	char	*dest;
	size_t	len;
	long	ret;

	ret = 1;
	len = gnlen(src);
	dest = ft_calloc(sizeof(char), len + 1);
	if (!dest)
		return (NULL);
	ft_strcpy(dest, src, len);
	update_nl(src);
	while (dest && dest[len - 1] != '\n' && ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret > 0)
		{
			ft_strcpy(src, buffer, ret);
			dest = gnl_join(dest, src);
			update_nl(src);
			len = gnlen(dest);
		}
		else if (ret < 0)
			return (gnfree(dest));
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	nl[BUFFER_SIZE + 1] = "\0";
	char		buffer[BUFFER_SIZE];
	long		ret;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (nl[0] == '\0')
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 1)
			return (NULL);
		ft_strcpy(nl, buffer, ret);
	}
	return (gnl_copy(nl, fd, buffer));
}

size_t	gnlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		++i;
	if (str[i] == '\n')
		++i;
	return (i);
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