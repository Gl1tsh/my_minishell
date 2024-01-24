/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:57:44 by tomuller          #+#    #+#             */
/*   Updated: 2024/01/23 17:19:46 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIST_H
# define ALIST_H

# include <stdlib.h>

// Amiga double linked lists
// https://wiki.amigaos.net/wiki/Exec_Lists_and_Queues

typedef struct s_anode
{
	struct s_anode	*succ;
	struct s_anode	*pred;
}	t_anode;

typedef struct s_alist
{
	t_anode	*head;
	t_anode	*tail;
	t_anode	*tail_pred;
}	t_alist;

void	alist_new_list(t_alist *list);
t_anode	*alist_get_head(t_alist *list);
t_anode	*alist_get_tail(t_alist *list);
t_anode	*alist_get_succ(t_anode *node);
t_anode	*alist_get_pred(t_anode *node);
void	alist_add_head(t_alist *list, t_anode *node);
void	alist_add_tail(t_alist *list, t_anode *node);
t_anode	*alist_rem_head(t_alist *list);
t_anode	*alist_rem_tail(t_alist *list);
void	alist_remove(t_anode *node);
void	alist_insert(t_alist *list, t_anode *node, t_anode *pred);
int		alist_is_empty(t_alist *list);
int		alist_size(t_alist *list);
t_alist	*alist_find_list_from(t_anode *node);
void	alist_each(t_alist *list, void (*f)(void *));
t_anode	*alist_find(t_alist *list, int (*predicate)(void *));

#endif	// ALIST_H
