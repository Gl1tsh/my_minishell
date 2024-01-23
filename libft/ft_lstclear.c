/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:08:11 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/26 17:26:38 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Supprime et libère la mémoire de tous les éléments de   */
/*   la liste en utilisant la fonction de suppression 'del'.                  */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - lst : Un pointeur vers un pointeur de liste. Lorsque la fonction    */
/*              termine, 'lst' est défini à NULL pour indiquer que la liste   */
/*              est maintenant vide.                                          */
/*      - del : Un pointeur vers une fonction qui prend un argument de type   */
/*              'void *' et libère la mémoire associée à cet argument.        */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	(*lst) = 0;
}
