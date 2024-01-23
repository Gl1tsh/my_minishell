/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:14:42 by powlar            #+#    #+#             */
/*   Updated: 2023/10/23 16:08:39 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Recherche la dernière occurrence du caractère 'c' dans  */
/*   la chaîne de caractères 's'.                                             */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - s : La chaîne de caractères dans laquelle rechercher                */
/*      - c : Le caractère à rechercher                                       */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Un pointeur vers la dernière occurrence de 'c' dans 's' si elle     */
/*        est trouvée, sinon NULL.                                            */
/* *****************************************************************   by.XVI */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *) s + i);
		i--;
	}
	return (0);
}
