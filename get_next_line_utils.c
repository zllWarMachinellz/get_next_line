/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidtor <davidtor@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:55:51 by davidtor          #+#    #+#             */
/*   Updated: 2024/01/10 18:04:28 by davidtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	search_n(t_nodo *lst)
{
	int	i;

	if (lst == NULL)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->s[i] && lst->next == NULL)
		{
			if (lst->s[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

t_nodo	*lst_last(t_nodo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	fill_node(t_nodo **lst, char *buf)
{
	t_nodo	*last_node;
	t_nodo	*new_node;

	new_node = malloc(sizeof(t_nodo));
	if (!new_node)
		return (-1);
	last_node = lst_last(*lst);
	if (!last_node)
		*lst = new_node;
	else
		last_node->next = new_node;
	new_node->s = buf;
	new_node->next = NULL;
	return (0);
}

int	fill_list(t_nodo **lst, int fd)
{
	char	*buf;
	ssize_t	validator;

	while (!search_n(*lst))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (-1);
		validator = read(fd, buf, BUFFER_SIZE);
		if (!validator)
			return (free(buf), 0);
		buf[validator] = '\0';
		if (fill_node(lst, buf) == -1)
			return (free(buf), -1);
	}
	return (0);
}

int	get_lst_len(t_nodo *lst)
{
	int	count;
	int	i;

	if (lst == NULL)
		return (0);
	count = 0;
	while (lst)
	{
		i = 0;
		while (lst->s[i])
		{
			if (lst->s[i] == '\n')
				return (++count);
			i++;
			count++;
		}
		lst = lst->next;
	}
	return (count);
}
