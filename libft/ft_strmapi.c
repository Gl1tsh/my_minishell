/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:33:00 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/26 14:40:26 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* *****************************  DESCRIPTION  ****************************** */
/*
La fonction ft_strmapi crée une nouvelle chaîne en appliquant la fonction 
spécifiée à chaque caractère de la chaîne d'entrée. Elle détermine d'abord la 
longueur de la chaîne d'entrée à l'aide de la fonction d'aide str_len. 

De la mémoire est allouée pour stocker la chaîne résultante, y compris de 
l'espace pour le caractère nul. Si l'allocation de mémoire échoue, 
NULL est renvoyé.

Ensuite, la fonction itère sur chaque caractère de la 
chaîne d'entrée, en transmettant l'index et le caractère actuels à la 
fonction fournie.

La fonction renvoie un nouveau caractère basé sur l'index 
et le caractère d'entrée, qui est stocké dans la chaîne résultante. Enfin, 
le terminateur nul est ajouté et la chaîne résultante est renvoyée.
*/

#include "libft.h"

static size_t	ft_strlen_mapi(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

static char	*str_new(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;
	char	*result;

	if (s == NULL)
		return (NULL);
	str = str_new(ft_strlen_mapi(s));
	if (str == NULL)
		return (NULL);
	i = 0;
	result = str;
	while (*s)
		*str++ = f(i++, *s++);
	*str = '\0';
	return (result);
}
