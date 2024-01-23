/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:38:21 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/03 19:38:21 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* Fonctionnement :  Convertit une chaîne de caractères en int.               */
/* Paramètre :       Chaîne de caractères str.                                */
/* Retour :          Un int.                                                  */
/* Si échec :        La fonction renvoie 0 si la chaîne ne contient pas       */
/*                   de chiffres valides ou si le résultat dépasse la plage   */
/*                   d'un int.                                                */
/* *****************************************************************   by.XVI */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}
