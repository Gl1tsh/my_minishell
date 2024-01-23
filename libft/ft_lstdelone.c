/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:50:54 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/26 17:26:55 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Supprime un élément de la liste sans supprimer la       */
/*   structure de donnée qu'il contenait.                                     */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - lst : L'élément de liste à supprimer.                               */
/*      - del : La fonction à utiliser pour supprimer le contenu de lst.      */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
}
