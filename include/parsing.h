/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 08:21:43 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/10 08:24:58 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

t_arg	*allocate_arg(t_arg *prev_arg);
t_cmd	*allocate_cmd(t_cmd *prev_cmd);
char	*skip_whitespace(char *input);

#endif