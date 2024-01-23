/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:38:28 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/23 16:12:06 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Remplit les len premiers octets de la zone mémoire      */
/*   pointée par b avec la valeur c (convertie en unsigned char).             */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - s : Un pointeur vers la zone mémoire à remplir                      */
/*      - c : La valeur à copier (convertie en unsigned char)                 */
/*      - n : Le nombre d'octets à remplir                                    */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Un pointeur vers la zone mémoire remplie (b).                       */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*s2;

	s2 = (char *)s;
	i = 0;
	while (i < n)
	{
		s2[i] = c;
		i++;
	}
	return (s);
}

/*
int main()

{
	char buffer[10];
	int age = 42;
	float pi = 3.14159216;

	ft_memset(buffer, 'p', 5);
	
}
*/