/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                               :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:52:33 by zivanov           #+#    #+#             */
/*   Updated: 2024/12/19 16:50:18 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

t_linked_list	*ft_last_element(t_linked_list **ptr_to_list)
{
	t_linked_list	*last_element;

	if (*ptr_to_list == NULL)
		return (NULL);
	last_element = *ptr_to_list;
	while ((last_element)->next != NULL)
		last_element = last_element->next;
	return (last_element);
}

int	ft_append(t_linked_list **total_list, char *buffer)
{
	t_linked_list	*new_element;
	t_linked_list	*last_element;

	last_element = ft_last_element(total_list);
	new_element = (t_linked_list *)malloc(sizeof(t_linked_list));
	if (new_element == NULL)
		return (free(buffer), -1);
	if (last_element == NULL)
		*total_list = new_element;
	else
		last_element->next = new_element;
	new_element->str = buffer;
	new_element->next = NULL;
	return (1);
}

ssize_t	ft_search_new_line(char *buffer)
{
	ssize_t	i;

	i = 0;
	if (buffer)
	{
		while (buffer[i])
		{
			if (buffer[i] == '\n')
				return (i);
			i++;
		}
		return (-2);
	}
	else
		return (-2);
}

size_t	ft_list_len(t_linked_list *complete_list)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (complete_list)
	{
		i = 0;
		while (complete_list->str[i] != '\0')
		{
			len++;
			if (complete_list->str[i] == '\n')
				return (len);
			i++;
		}
		complete_list = complete_list->next;
	}
	return (len);
}

void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
