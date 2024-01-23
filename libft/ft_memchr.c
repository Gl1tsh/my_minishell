/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:53:44 by powlar            #+#    #+#             */
/*   Updated: 2023/10/23 16:04:40 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Recherche la première occurrence de l'octet c dans les  */
/*   n premiers octets dans la zone mémoire pointée par s.                    */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - s : Un pointeur vers la zone mémoire à analyser                     */
/*      - c : L'octet à rechercher                                            */
/*      - n : Le nombre d'octets à analyser                                   */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Un pointeur vers la première occurrence de c dans s,                */
/*        ou NULL si c n'est pas trouvé.                                      */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_s;
	unsigned char	chr;

	ptr_s = (unsigned char *)s;
	chr = (unsigned char)c;
	while (n)
	{
		if (*ptr_s == chr)
			return (ptr_s);
		n--;
		ptr_s++;
	}
	return (0);
}
