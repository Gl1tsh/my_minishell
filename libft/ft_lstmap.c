/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:42:12 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/26 17:28:07 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Applique la fonction 'f' à chaque élément de la liste,  */
/*   crée une nouvelle liste avec les résultats et retourne un pointeur vers  */
/*   la nouvelle lst. En cas d'échec d'allocation mémoire, libère la nouvelle */
/*   liste ainsi que son contenu en utilisant 'del' et renvoie NULL.          */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - lst : Un pointeur vers le premier élément de la liste à mapper.     */
/*      - f : La fonction à appliquer à chaque élément de la liste.           */
/*      - del : La fonction à utiliser pour supprimer le contenu en cas       */
/*              d'échec d'allocation mémoire.                                 */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Un pointeur vers la nouvelle liste créée.                           */
/*      - NULL en cas d'échec d'allocation mémoire ou si 'lst' est NULL.      */
/*                                                                            */
/*   Si échec :                                                               */
/*      La fonction libère la nouvelle liste ainsi que son contenu en cas     */
/*      d'échec d'allocation mémoire et renvoie NULL.                         */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_content;

	if (lst == NULL)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		new_content = ft_lstnew((*f)(lst->content));
		if (new_content == NULL)
		{
			ft_lstclear(&new_content, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_content);
		lst = lst->next;
	}
	return (new_lst);
}
