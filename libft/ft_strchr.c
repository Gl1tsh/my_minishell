/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:52:45 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/23 16:11:02 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Recherche la première occurrence du caractère 'c' dans  */
/*   la chaîne de caractères 's'.                                             */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - s : La chaîne de caractères dans laquelle effectuer la recherche    */
/*      - i : Le caractère à rechercher                                       */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Un pointeur vers la première occurrence de 'i' dans 's'.            */
/*      - NULL si 'i' n'est pas trouvé dans 's'.                              */
/* *****************************************************************   by.XVI */

#include "libft.h"

char	*ft_strchr(const char *s, int i)
{
	i %= 256;
	while (*s)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	if (i == '\0')
		return ((char *)s);
	return (0);
}
