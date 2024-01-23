/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:30:44 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/26 17:27:14 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Applique la fonction 'f' à chaque 'content' de 'lst'.   */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - lst : Un pointeur vers le premier élément de la liste.              */
/*      - f : Un pointeur vers la fonction à appliquer à chaque élément.      */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
