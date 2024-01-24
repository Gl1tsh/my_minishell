/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:57:44 by tomuller          #+#    #+#             */
/*   Updated: 2024/01/23 17:19:46 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dstr.h"

void	dstr_allocate(t_dstr *buffer, size_t size)
{
	buffer->bytes = ft_calloc(1, size + 1);
	buffer->allocated_size = size;
	buffer->used_size = 0;
}

void	dstr_free(t_dstr *buffer)
{
	free(buffer->bytes);
}

void	dstr_ensure(t_dstr *buffer, size_t size)
{
	char	*new_bytes;

	if (buffer->allocated_size < size)
	{
		buffer->allocated_size = size + 16;
		new_bytes = ft_calloc(1, buffer->allocated_size + 1);
		ft_memcpy(new_bytes, buffer->bytes, buffer->used_size);
		free(buffer->bytes);
		buffer->bytes = new_bytes;
	}
	buffer->used_size = size;
}

void	dstr_append(t_dstr *buffer, char *str, size_t length)
{
	dstr_ensure(buffer, buffer->used_size + length);
	ft_strlcat(buffer->bytes, str, buffer->used_size + 1);
}
