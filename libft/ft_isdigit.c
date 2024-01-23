/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:38:46 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/23 16:12:50 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Vérifie si le caractère passé en argument est un        */
/*   caractère ASCII.                                                         */
/*                                                                            */
/*   Paramètre :                                                              */
/*      - i : Le caractère à vérifier                                         */
/*                                                                            */
/*   Retour :                                                                 */
/*      - 1 si i est un caractère ASCII, sinon 0                              */
/* *****************************************************************   by.XVI */

#include "libft.h"

int	ft_isdigit(int i)
{
	if (i >= '0' && i <= '9')
		return (1);
	return (0);
}
