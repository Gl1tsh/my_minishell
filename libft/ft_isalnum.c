/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:38:29 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/23 16:13:10 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Vérifie si le caractère passé en argument est un        */
/*   caractère alphanumérique.                                                */
/*                                                                            */
/*   Paramètre :                                                              */
/*      - i : Le caractère à vérifier                                         */
/*                                                                            */
/*   Retour :                                                                 */
/*      - 1 si i est un caractère alphanumérique, sinon 0                     */
/* *****************************************************************   by.XVI */

#include "libft.h"

int	ft_isalnum(int i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z')
		|| (i >= '0' && i <= '9'))
		return (1);
	return (0);
}
