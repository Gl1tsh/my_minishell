/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:40:06 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/23 16:12:14 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Copie les len premiers octets de la zone mémoire        */
/*   pointée par src dans la zone mémoire pointée par dst.                    */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - dst : Un pointeur vers la zone mémoire de destination               */
/*      - src : Un pointeur vers la zone mémoire source à copier              */
/*      - n : Le nombre d'octets à copier                                     */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Un pointeur vers la zone mémoire de destination (dst).              */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (dest > src)
	{
		while (n--)
			d[n] = s[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
