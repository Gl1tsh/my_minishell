/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:44:08 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/24 16:14:17 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Copie la chaîne de caractères 'src' dans 'dst' avec     */
/*   une taille maximale de 'dstsize'. Si 'dstsize' est supérieur à la        */
/*   longueur de 'src', la fonction copie toute la chaîne 'src' dans 'dst'    */
/*   et ajoute un caractère nul à la fin. Sinon, elle copie 'dstsize - 1'     */
/*   caractères de 'src' dans 'dst' et ajoute un caractère nul à la fin.      */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - dst : La chaîne de caractères de destination                        */
/*      - src : La chaîne de caractères source à copier                       */
/*      - size : La taille maximale de 'dst'                               */
/*                                                                            */
/*   Retour :                                                                 */
/*      La longueur de la chaîne 'src' (c'est-à-dire le nombre de caractères  */
/*      dans 'src', sans tenir compte du caractère nul de fin).               */
/* *****************************************************************   by.XVI */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src [i] != '\0' && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}
