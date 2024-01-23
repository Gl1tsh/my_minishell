/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:24:38 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/24 17:56:55 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Écrit la chaîne de caractères 's' dans le descripteur   */
/*   de fichier 'fd'.                                                         */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - str : La chaîne de caractères à écrire                              */
/*      - fd : Le descripteur de fichier où écrire la chaîne de caractères.   */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
	{
		write(fd, &*str++, 1);
	}
}
