/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidtor <davidtor@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:52:57 by davidtor          #+#    #+#             */
/*   Updated: 2024/01/10 17:28:20 by davidtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_nodes(t_nodo **lst)
{
	t_nodo	*temp;

	temp = *lst;
	while (*lst)
	{
		*lst = (*lst)->next;
		free(temp->s);
		free(temp);
		temp = *lst;
	}
	*lst = NULL;
}

char	*get_len_cpy(t_nodo *lst, char *arr)
{
	int	i;
	int	j;

	if (lst == NULL)
		return (free(arr), NULL);
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->s[i])
		{
			if (lst->s[i] == '\n')
			{
				arr[j++] = '\n';
				arr[j] = '\0';
				return (arr);
			}
			arr[j++] = lst->s[i++];
		}
		lst = lst->next;
	}
	arr[j] = '\0';
	return (arr);
}

void	clean_all_list(t_nodo **lst, char *buf, t_nodo *new_node)
{
	t_nodo	*temp;

	temp = *lst;
	while (*lst)
	{
		*lst = (*lst)->next;
		free(temp->s);
		free(temp);
		temp = *lst;
	}
	*lst = NULL;
	if (new_node->s[0])
		*lst = new_node;
	else
	{
		free(buf);
		free(new_node);
	}
}

int	free_list(t_nodo **lst)
{
	int		i;
	int		j;
	t_nodo	*last_node;
	char	*buf;
	t_nodo	*new_node;

	new_node = malloc(sizeof(t_nodo));
	if (!new_node)
		return (-1);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(new_node), -1);
	last_node = lst_last(*lst);
	i = 0;
	while (last_node->s[i] != '\n' && last_node->s[i] != '\0')
		i++;
	j = 0;
	while (last_node->s[i] != '\0')
		buf[j++] = last_node->s[++i];
	buf[j] = '\0';
	new_node->s = buf;
	new_node->next = NULL;
	clean_all_list(lst, buf, new_node);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_nodo	*root;
	char			*line;
	char			*arr;
	int				lst_len;
	int				validator;

	if (read(fd, &line, 0) < 0)
		return (free_nodes(&root), NULL);
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	validator = fill_list(&root, fd);
	if (!root || validator == -1)
		return (free_nodes(&root), NULL);
	lst_len = get_lst_len(root);
	arr = malloc(sizeof(char) * (lst_len + 1));
	if (!arr)
		return (free_nodes(&root), NULL);
	line = get_len_cpy(root, arr);
	if (!line)
		return (free_nodes(&root), free(arr), NULL);
	validator = free_list(&root);
	if (validator == -1)
		return (free_nodes(&root), free(arr), NULL);
	return (line);
}
