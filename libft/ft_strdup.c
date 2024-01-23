/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:38:56 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/03 19:38:56 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Duplique une chaîne de caractères 's1' dans une         */
/*   nouvelle allocation mémoire.                                             */
/*                                                                            */
/*   Paramètre :                                                              */
/*      - src : La chaîne de caractères à dupliquer                           */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Un pointeur vers la nouvelle chaîne de caractères dupliquée.        */
/*      - NULL en cas d'échec d'allocation mémoire.                           */
/* *****************************************************************   by.XVI */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	size_t	src_length;
	char	*dest;

	src_length = ft_strlen(src);
	dest = malloc(sizeof(char) * src_length + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
