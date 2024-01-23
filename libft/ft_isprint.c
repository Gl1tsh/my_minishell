/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:38:49 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/03 19:38:49 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Vérifie si le caractère passé en argument est un        */
/*   caractère imprimable de l'ASCII (code 32 à 126 inclus).                  */
/*                                                                            */
/*   Paramètre :                                                              */
/*      - i : Le caractère à vérifier                                         */
/*                                                                            */
/*   Retour :                                                                 */
/*      - 1 si i est un caractère imprimable de l'ASCII, sinon 0              */
/* *****************************************************************   by.XVI */

#include "libft.h"

int	ft_isprint(int i)
{
	if (i >= 32 && i <= 126)
		return (1);
	return (0);
}
