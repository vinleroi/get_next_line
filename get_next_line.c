/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 03:32:42 by aahadji           #+#    #+#             */
/*   Updated: 2024/11/24 09:12:11 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*next_lines = NULL;
	char			*line;
	int				len;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	len = 1;
	line = NULL;
	stack_read_lines(fd, &next_lines, &len);
	if (next_lines == NULL)
		return (NULL);
	extract_line(next_lines, &line);
	clean_stack(&next_lines);
	if (line[0] == '\0')
	{
		free_stack(next_lines);
		next_lines = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
stack_read_lines(int fd, t_list **stack, int *len)
{
	char	*buffer;

	while (!found_new_line(*stack) && *len != 0)
	{
		buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		*len = (int)read(fd, buffer, BUFFER_SIZE);
		if ((*stack == NULL && *len == 0) || *len == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[*len] = '\0';
		ft_lstadd(stack, buffer, *len);
		free(buffer);
	}
}
void	ft_lstadd(t_list **list, char *buffer, int len)
{
	int		i;
	t_list	*new_node;
	t_list	*last;

	new_node = ft_calloc(sizeof(t_list), 1);
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->str_buf = ft_calloc(sizeof(char), len + 1);
	if (new_node->str_buf == NULL)
		return (NULL);
	ft_strcpy(new_node->str_buf, buffer);
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	last = ft_lstlast(*list);
	last->next = new_node;
}
void	extract_line(t_list *stack, char **line)
{
	int	i;
	int	j;

	if (stack == NULL)
		return ;
	sizeof_line(line, stack);
	if (!line)
		return (NULL);
	j = 0;
	while (stack)
	{
		i = 0;
		while (stack->str_buf[i])
		{
			if (stack->str_buf[i] == '\n')
			{
				(*line)[j++] = stack->str_buf[i];
				break ;
			}
			(*line)[j++] = stack->str_buf[i++];
		}
		stack = stack->next;
	}
	(*line)[j] = '\0';
}

void	sizeof_line(char **line, t_list *stack)
{
	int	i;
	int	len;

	len = 0;
	while (stack)
	{
		i = 0;
		while (stack->str_buf[i])
		{
			if (stack->str_buf[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stack = stack->next;
	}
	*line = ft_calloc(sizeof(char), len + 1);
}

void	clean_stack(t_list **stack)
{
	t_list	*last;
	t_list	*cln_node;
	int		i;
	int		j;

	cln_node = ft_calloc(sizeof(t_list), 1);
	if (stack == NULL || cln_node == NULL)
		return ;
	cln_node->next = NULL;
	last = ft_lstlast(stack);
	i = 0;
	while (last->str_buf[i] && last->str_buf[i] == '\n')
		i++;
	if (last->str_buf[i] && last->str_buf[i] == '\n')
		i++;
	cln_node->str_buf = ft_calloc(sizeof(char), (ft_strlen(last->str_buf) - i
				+ 1));
	if (cln_node->str_buf == NULL)
		return ;
	j = 0;
	while (last->str_buf[i])
		cln_node->str_buf[j++] = last->str_buf[i++];
	cln_node->str_buf[j] = '/0';
	free_stack(*stack);
	*stack = cln_node;
}

void	free_stack(t_list *stack)
{
	t_list *current;
	t_list *next_node;

	if (!stack)
		return ;
	current = stack;
	while (current)
	{
		free(current->str_buf);
		next_node = current->next;
		free(current);
		current = next_node;
	}
}