/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:46:05 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/23 16:13:17 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Remplit les n premiers octets de la mémoire pointée par */
/*   s avec l'octet nul (valeur 0).                                           */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - s : Un pointeur vers la mémoire à remplir                           */
/*      - n : Le nombre d'octets à remplir                                    */
/*                                                                            */
/*   Retour :                                                                 */
/*      Aucun                                                                 */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*s2;

	s2 = (char *)s;
	i = 0;
	while (i < n)
	{
		s2[i] = 0;
		i++;
	}
}

/*
void bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
*/