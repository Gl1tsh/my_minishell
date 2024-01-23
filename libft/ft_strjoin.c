/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:54:41 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/23 16:07:20 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Alloue et retourne une nouvelle chaîne de caractères    */
/*   résultant de la concaténation de 's1' suivi de 's2'.                     */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - s1 : La première chaîne de caractères                               */
/*      - s2 : La deuxième chaîne de caractères                               */
/*                                                                            */
/*   Retour :                                                                 */
/*      Un pointeur vers la nouvelle chaîne de caractères, ou NULL si         */
/*      l'allocation échoue.                                                  */
/* *****************************************************************   by.XVI */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*dest;
	int		i;
	int		c;

	i = 0;
	c = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = malloc(sizeof(char) * size);
	if (!dest)
		return (NULL);
	while (s1[i])
		dest[c++] = s1[i++];
	i = 0;
	while (s2[i])
		dest[c++] = s2[i++];
	dest[c] = '\0';
	return (dest);
}
