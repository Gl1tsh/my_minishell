/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:15:05 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/23 16:10:17 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Recherche une sous-chaîne 'needle' dans une chaîne de   */
/*   caractères 'haystack' en vérifiant selon 'len' caractères.               */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - haystack : La chaîne de caractères dans laquelle rechercher         */
/*      - needle : La sous-chaîne à rechercher                                */
/*      - n : Le nombre maximum de caractères à vérifier dans 'haystack'      */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Un pointeur vers la première occurrence de 'needle' dans 'haystack' */
/*        si elle est trouvée, sinon NULL.                                    */
/* *****************************************************************   by.XVI */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < n)
	{
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j] && i + j < n)
			{
				if (needle[j + 1] == '\0')
					return ((char *)haystack + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
