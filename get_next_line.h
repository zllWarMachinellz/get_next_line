/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidtor <davidtor@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:53:57 by davidtor          #+#    #+#             */
/*   Updated: 2024/01/10 17:24:14 by davidtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_node
{
	char			*s;
	struct s_node	*next;
}	t_nodo;

char	*get_next_line(int fd);
int		search_n(t_nodo *lst);
t_nodo	*lst_last(t_nodo *lst);
int		fill_node(t_nodo **lst, char *buf);
int		fill_list(t_nodo **lst, int fd);
int		get_lst_len(t_nodo *lst);
void	free_nodes(t_nodo **lst);
char	*get_len_cpy(t_nodo *lst, char *arr);
void		clean_all_list(t_nodo **lst, char *buf, t_nodo *new_node);
int		free_list(t_nodo **lst);

#endif
