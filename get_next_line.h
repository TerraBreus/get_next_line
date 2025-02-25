/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                     :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:52:25 by zivanov           #+#    #+#             */
/*   Updated: 2024/12/19 16:09:04 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>

typedef struct Node
{
	char		*str;
	struct Node	*next;
}	t_linked_list;

char			*get_next_line(int fd);
int				create_list(t_linked_list **total_list, int fd);
char			*conc_lists(t_linked_list *complete_list);
int				clean_list(t_linked_list **list);
void			ft_free_all(t_linked_list **list, t_linked_list *new_list);
void			ft_free(void *ptr);
size_t			ft_list_len(t_linked_list *complete_list);
ssize_t			ft_search_new_line(char *buffer);
int				ft_append(t_linked_list **total_list, char *buffer);
t_linked_list	*ft_last_element(t_linked_list **ptr_to_list);

#endif
