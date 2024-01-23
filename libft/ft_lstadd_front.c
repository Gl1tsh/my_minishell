/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:43:05 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/26 17:26:11 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Ajoute un nouvel élément en tête de la liste chaînée.   */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - lst : Un pointeur vers un pointeur de liste, qui pointe vers la     */
/*              tête de la liste à laquelle ajouter l'élément.                */
/*      - new : Un pointeur vers l'élément de liste à ajouter en tête.        */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst)
		new->next = *lst;
	*lst = new;
}
