/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:39:02 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/03 19:39:02 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Convertit un caractère majuscule en caractère minuscule */
/*   si c'est une lettre majuscule. Sinon, renvoie le caractère inchangé.     */
/*                                                                            */
/*   Paramètre :                                                              */
/*      - i : Le caractère à convertir                                        */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Le caractère converti si c'est une lettre majuscule, sinon c        */
/*        caractère inchangé.                                                 */
/* *****************************************************************   by.XVI */

#include "libft.h"

int	ft_tolower(int i)
{
	if (i >= 'A' && i <= 'Z')
		return (i + 32);
	return (i);
}
