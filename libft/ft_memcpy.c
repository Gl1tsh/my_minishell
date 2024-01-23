/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:21:04 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/25 15:48:15 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*   Fonctionnement : Copie les n premiers octets de la zone mémoire pointée  */
/*   par src dans la zone mémoire pointée par dst.                            */
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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	s = (char *)src;
	d = (char *)dest;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
