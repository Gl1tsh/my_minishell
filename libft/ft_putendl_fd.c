/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:40:06 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/24 17:57:12 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Écrit la chaîne de caractères 's' suivie d'un saut de   */
/*   ligne dans le descripteur de fichier 'fd'.                               */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - str : La chaîne de caractères à écrire                              */
/*      - fd : Le descripteur de fichier où écrire la chaîne et le saut de    */
/*        ligne                                                               */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	ft_putendl_fd(char *str, int fd)
{
	while (*str)
	{
		write(fd, &*str++, 1);
	}
	write(fd, "\n", 1);
}
