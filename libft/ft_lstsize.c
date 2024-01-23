/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:21:54 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/26 17:28:32 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Calcule la taille de la liste chaînée.                  */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - lst : Un pointeur vers la tête de la liste chaînée dont on veut     */
/*              calculer la taille.                                           */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Le nombre d'éléments dans la liste chaînée.                         */
/* *****************************************************************   by.XVI */

#include "libft.h"

int	ft_lstsize(t_list *lama)
{
	size_t	i;

	i = 0;
	while (lama != NULL)
	{
		i++;
		lama = lama->next;
	}
	return (i);
}
