/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:17:29 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/29 16:22:34 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Fonctionnement : Divise une chaîne de caractères en mots en utilisant    */
/*   la variable 'separator' comme séparateur.                                */
/*                                                                            */
/*   Paramètres :                                                             */
/*      - str : La chaîne de caractères à diviser                             */
/*      - separator : Le caractère de séparation                              */
/*                                                                            */
/*   Retour :                                                                 */
/*      - Un tableau de chaînes de caractères contenant les mots extraits de  */
/*        'str'. Le tableau est terminé par un pointeur NULL.                 */
/*      - NULL en cas d'échec (allocation mémoire ou paramètre invalide).     */
/*                                                                            */
/*   Si échec :                                                               */
/*      - La fonction renvoie NULL si l'allocation mémoire échoue ou si 'str' */
/*        est NULL.                                                           */
/* *****************************************************************   by.XVI */

#include "libft.h"

int	count_words(const char *str, char separator)
{
	int	i;
	int	number_of_word;

	i = 0;
	number_of_word = 0;
	while (str[i])
	{
		if (str[i] != separator)
		{
			number_of_word++;
			while (str[i] != separator && str[i] != '\0')
				i++;
		}
		else
		{
			if (str[i] == separator && str[i])
			{
				while (str[i] != '\0' && str[i] == separator)
					i++;
			}
		}
	}
	return (number_of_word);
}

char	*word_dup(const char *str, int start, int finish)
{
	char	*duplicated_word;
	int		i;

	i = 0;
	duplicated_word = (char *)malloc(sizeof(char) * (finish - start + 1));
	if (duplicated_word == NULL)
		return (NULL);
	while (start < finish)
	{
		duplicated_word[i] = str[start];
		i++;
		start++;
	}
	duplicated_word[i] = '\0';
	return (duplicated_word);
}

char	**ft_split(char const *s, char sep)
{
	size_t	i;
	size_t	word_index;
	int		word_start_pos;
	char	**result;

	result = (char **)malloc((count_words(s, sep) + 1) * sizeof(char *));
	if (s == NULL || result == NULL)
		return (NULL);
	i = 0;
	word_index = 0;
	word_start_pos = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != sep && word_start_pos < 0)
			word_start_pos = i;
		else if ((s[i] == sep || i == ft_strlen(s)) && word_start_pos >= 0)
		{
			result[word_index] = word_dup(s, word_start_pos, i);
			word_index++;
			word_start_pos = -1;
		}
		i++;
	}
	result[word_index] = 0;
	return (result);
}
