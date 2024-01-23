/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:39:05 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/03 19:39:05 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Convertit un caractère minuscule en majuscule           */
/*   si c'est une lettre minuscule. Sinon, renvoie le caractère inchangé.     */
/*                                                                            */
/*   Paramètre :                                                              */
/*      - i : Le caractère à convertir                                        */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Le caractère converti si c'est une lettre minuscule, sinon c        */
/*        caractère inchangé.                                                 */
/* *****************************************************************   by.XVI */

#include "libft.h"

int	ft_toupper(int i)
{
	if (i >= 'a' && i <= 'z')
		return (i - 32);
	return (i);
}
