/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                     :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:52:38 by zivanov           #+#    #+#             */
/*   Updated: 2024/12/19 16:40:58 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

int	create_list(t_linked_list **total_list, int fd)
{
	char	*buffer;
	ssize_t	char_read;

	char_read = -2;
	if (ft_last_element(total_list) != NULL)
		char_read = ft_search_new_line((ft_last_element(total_list))->str);
	while (char_read == -2)
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (-1);
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read > 0)
		{
			buffer[char_read] = '\0';
			if (ft_append(total_list, buffer) == -1)
				return (-1);
			char_read = ft_search_new_line(buffer);
		}
		else if (char_read == 0)
			free(buffer);
		else
			return (free(buffer), -1);
	}
	return (1);
}

char	*conc_lists(t_linked_list *complete_list)
{
	size_t	i;
	size_t	j;
	char	*total_str;

	if (complete_list == NULL)
		return (NULL);
	total_str = (char *)malloc(sizeof(char) * (ft_list_len(complete_list) + 1));
	if (total_str == NULL)
		return (NULL);
	j = 0;
	while (complete_list)
	{
		i = 0;
		while (complete_list->str[i] != '\0')
		{
			total_str[j] = complete_list->str[i];
			j++;
			if (complete_list->str[i] == '\n')
				break ;
			i++;
		}
		complete_list = complete_list->next;
	}
	total_str[j] = '\0';
	return (total_str);
}

int	clean_list(t_linked_list **list)
{
	t_linked_list	*last_element;
	t_linked_list	*new_list;
	char			*left_over_buffer;
	ssize_t			i;
	size_t			j;

	last_element = ft_last_element(list);
	if (!last_element)
		return (-1);
	i = ft_search_new_line(last_element->str) + 1;
	if (i < 0)
		return (ft_free_all(list, NULL), 1);
	left_over_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (left_over_buffer == NULL)
		return (-1);
	j = 0;
	while (last_element->str[i])
		left_over_buffer[j++] = last_element->str[i++];
	left_over_buffer[j] = '\0';
	new_list = (t_linked_list *)malloc(sizeof(t_linked_list));
	if (new_list == NULL)
		return (ft_free(left_over_buffer), -1);
	new_list->next = NULL;
	new_list->str = left_over_buffer;
	return (ft_free_all(list, new_list), 1);
}

void	ft_free_all(t_linked_list **list, t_linked_list *new_list)
{
	t_linked_list	*temp;

	while (*list)
	{
		temp = (*list)->next;
		ft_free((*list)->str);
		ft_free(*list);
		*list = temp;
	}
	if (new_list)
	{
		if (new_list->str[0])
			*list = new_list;
		else
		{
			ft_free(new_list->str);
			ft_free(new_list);
			*list = NULL;
		}
	}
	else
		*list = new_list;
}

char	*get_next_line(int fd)
{
	static t_linked_list	*total_list;
	char					*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (create_list(&total_list, fd) == -1)
	{
		ft_free_all(&total_list, NULL);
		return (NULL);
	}
	next_line = conc_lists(total_list);
	if (next_line == NULL)
	{
		ft_free_all(&total_list, NULL);
		return (NULL);
	}
	if (clean_list(&total_list) == -1)
	{
		ft_free_all(&total_list, NULL);
		free(next_line);
		return (NULL);
	}
	return (next_line);
}
