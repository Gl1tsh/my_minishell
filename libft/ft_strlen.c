/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:38:59 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/03 19:38:59 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Calcule la longueur de la chaîne de caractères 's'.     */
/*                                                                            */
/*   Paramètre :                                                              */
/*      - s : La chaîne de caractères dont on veut calculer la longueur.      */
/*                                                                            */
/*   Retour :                                                                 */
/*      La longueur de la chaîne 's' (c'est-à-dire le nombre de caractères    */
/*      dans 's', sans tenir compte du caractère nul de fin).                 */
/* *****************************************************************   by.XVI */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
