/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:56:56 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/01/24 18:01:36 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	int		i;
	size_t	src_length;
	char	*dest;

	src_length = ft_strlen(src);
	if (n < src_length)
		src_length = n;
	dest = malloc(sizeof(char) * src_length + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (src_length--)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
