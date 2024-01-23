/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:21:22 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/25 14:33:29 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Crée un nouvel élément de liste avec la donnée passée   */
/*   en argument.                                                             */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - content : La donnée à stocker dans le nouvel élément de liste.      */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Un pointeur vers le nouvel élément de liste créé.                   */
/*      - NULL en cas d'échec d'allocation de mémoire.                        */
/* *****************************************************************   by.XVI */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_list;

	new_list = malloc(sizeof(t_list));
	if (new_list == NULL)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}
