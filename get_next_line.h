/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:14:39 by aahadji           #+#    #+#             */
/*   Updated: 2024/11/24 08:49:47 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10 
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}				t_list;


char	*get_next_line(int fd);
void	*ft_calloc(size_t count, size_t size);
int	found_new_line(t_list *list);
t_list	*ft_lstlast(t_list *lst);
char	*ft_strcpy(char *dest, char *src);
size_t	ft_strlen(const char *str);


#endif