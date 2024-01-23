/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:33:28 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/26 17:29:15 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Applique la fonction 'f' à chaque caractère de la       */
/*   chaîne de caractères 's' en lui passant son index en premier argument.   */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - s : La chaîne de caractères à parcourir                             */
/*      - f : Le pointeur vers la fonction à appliquer à chaque caractère     */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
