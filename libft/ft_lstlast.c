/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:30:09 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/26 17:27:34 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Renvoie un pointeur vers le dernier élément de la liste */
/*   en parcourant la liste jusqu'à ce que le pointeur vers le prochain       */
/*   élément soit NULL.                                                       */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - lst : Un pointeur vers le premier élément de la liste.              */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Un pointeur vers le dernier élément de la liste.                    */
/*      - NULL si la liste est vide (lst == NULL).                            */
/* *****************************************************************   by.XVI */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}
