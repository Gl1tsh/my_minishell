/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:49:19 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/24 18:22:06 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Crée une nouvelle chaîne de caractères qui est une      */
/*   sous-chaîne de 's', débutant à l'index 'start' et d'une longueur 'len'.  */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - s : La chaîne de caractères source                                  */
/*      - start : L'index de départ pour la sous-chaîne                       */
/*      - len : La longueur de la sous-chaîne                                 */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Une nouvelle chaîne de caractères allouée dynamiquement             */
/*        contenant la sous-chaîne de 's'.                                    */
/* *****************************************************************   by.XVI */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub_str;
	unsigned int	source_len;
	unsigned int	i;

	source_len = ft_strlen(s);
	if (len > source_len)
		len = source_len;
	if (start >= source_len)
		start = source_len;
	if (start + len >= source_len)
		len = source_len - start;
	sub_str = malloc(sizeof(char) * (len + 1));
	if (sub_str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}
