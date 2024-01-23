/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:25:58 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/24 17:57:04 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Écrit l'entier 'n' dans le descripteur de fichier 'fd'  */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - nb : L'entier à écrire                                              */
/*      - fd : Le descripteur de fichier où écrire l'entier.                  */
/* *****************************************************************   by.XVI */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	i;

	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		i = -nb;
	}
	else
		i = nb;
	if (i > 9)
	{
		ft_putnbr_fd(i / 10, fd);
		i %= 10;
	}
	ft_putchar_fd(i + '0', fd);
}
