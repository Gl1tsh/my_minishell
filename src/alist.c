/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:57:44 by tomuller          #+#    #+#             */
/*   Updated: 2024/01/23 17:19:46 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alist.h"

void	alist_new_list(t_alist *list)
{
	list->head = (t_anode *)&list->tail;
	list->tail = NULL;
	list->tail_pred = (t_anode *)&list->head;
}

t_anode	*alist_get_head(t_alist *list)
{
	if (list->head->succ)
		return (list->head);
	else
		return (NULL);
}

t_anode	*alist_get_tail(t_alist *list)
{
	if (list->tail_pred->succ)
		return (list->tail_pred);
	else
		return (NULL);
}

t_anode	*alist_get_succ(t_anode *node)
{
	if (node->succ->succ)
		return (node->succ);
	else
		return (NULL);
}

t_anode	*alist_get_pred(t_anode *node)
{
	if (node->pred->pred)
		return (node->pred);
	else
		return (NULL);
}

void	alist_add_head(t_alist *list, t_anode *node)
{
	node->succ = list->head;
	node->pred = (t_anode *)&list->head;
	list->head->pred = node;
	list->head = node;
}

void	alist_add_tail(t_alist *list, t_anode *node)
{
	node->succ = (t_anode *)&list->tail;
	node->pred = list->tail_pred;
	list->tail_pred->succ = node;
	list->tail_pred = node;
}

t_anode	*alist_rem_head(t_alist *list)
{
	t_anode	*node;

	node = list->head->succ;
	if (node)
	{
		node->pred = (t_anode *)list;
		node = list->head;
		list->head = node->succ;
	}
	return (node);
}

t_anode	*alist_rem_tail(t_alist *list)
{
	t_anode	*node;

	node = alist_get_tail(list);
	if (node)
	{
		node->pred->succ = node->succ;
		node->succ->pred = node->pred;
	}
	return (node);
}

void	alist_remove(t_anode *node)
{
	node->pred->succ = node->succ;
	node->succ->pred = node->pred;
}

void	alist_insert(t_alist *list, t_anode *node, t_anode *pred)
{
	if (pred)
	{
		if (pred->succ)
		{
			node->succ = pred->succ;
			node->pred = pred;
			pred->succ->pred = node;
			pred->succ = node;
		}
		else
		{
			node->succ = (t_anode *)&list->tail;
			node->pred = list->tail_pred;
			list->tail_pred->succ = node;
			list->tail_pred = node;
		}
	}
	else
	{
		node->succ = list->head;
		node->pred = (t_anode *)&list->head;
		list->head->pred = node;
		list->head = node;
	}
}

int	alist_is_empty(t_alist *list)
{
	return (list->head->succ == NULL);
}

int	alist_size(t_alist *list)
{
	int		size;
	t_anode	*node;

	size = 0;
	node = list->head;
	while (node->succ != NULL)
	{
		size++;
		node = node->succ;
	}
	return (size);
}

t_alist	*alist_find_list_from(t_anode *node)
{
	t_alist	*head;

	head = NULL;
	if (node != NULL)
	{
		while (node->pred != NULL)
			node = node->pred;
		head = (t_alist *)node;
	}
	return (head);
}

// iterating over a list with safe removal from callback (if done)
void	alist_each(t_alist *list, void (*f)(void *))
{
	t_anode	*node;
	t_anode	*next;

	node = alist_get_head(list);
	while (node != NULL)
	{
		next = alist_get_succ(node);
		f(node);
		node = next;
	}
}

// iterating over a list to find the node matching predicate
t_anode	*alist_find(t_alist *list, int (*predicate)(void *))
{
	t_anode	*node;

	node = list->head;
	while (node->succ != NULL)
	{
		if (predicate(node))
			return (node);
		node = node->succ;
	}
	return (NULL);
}
