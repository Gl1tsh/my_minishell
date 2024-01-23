/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:19:12 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/23 16:02:53 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Alloue et initialise un bloc de mémoire à zéro.         */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - count : Le nombre d'éléments à allouer                              */
/*      - size : La taille de chaque élément                                  */
/*                                                                            */
/*   Retour :                                                                 */
/*      Un pointeur vers le bloc de mémoire alloué et initialisé à zéro.      */
/*      Si l'allocation échoue, la fonction renvoie NULL.                     */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	full_size;
	void	*ptr;

	full_size = count * size;
	ptr = malloc(full_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, full_size);
	return (ptr);
}
