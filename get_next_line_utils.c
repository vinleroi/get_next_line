/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 03:54:09 by aahadji           #+#    #+#             */
/*   Updated: 2024/11/24 08:49:38 by aahadji          ###   ########.fr       */
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

int	found_new_line(t_list *list)
{
	int		i;
	t_list	*current;

	if (list == NULL)
		return (0);
	current = ft_lstlast(list);
	i = 0;
	while (current->str_buf[i])
	{
		if (current->str_buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}