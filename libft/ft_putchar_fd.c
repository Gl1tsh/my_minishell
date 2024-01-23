/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:34:14 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/23 16:05:55 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Écrit le caractère 'c' dans le descripteur de fichier   */
/*   'fd'.                                                                    */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - c : Le caractère à écrire                                           */
/*      - fd : Le descripteur de fichier où écrire le caractère               */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
