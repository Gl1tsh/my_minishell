/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:57:44 by tomuller          #+#    #+#             */
/*   Updated: 2024/01/23 17:19:46 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DSTR_H
# define DSTR_H

# include "libft.h"

typedef struct s_dstr
{
	char	*bytes;
	size_t	used_size;
	size_t	allocated_size;
}	t_dstr;

void	dstr_allocate(t_dstr *buffer, size_t size);
void	dstr_free(t_dstr *buffer);
void	dstr_ensure(t_dstr *buffer, size_t size);
void	dstr_append(t_dstr *buffer, char *str, size_t length);

#endif	// DSTR_H
