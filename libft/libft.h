/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:39:09 by nagiorgi          #+#    #+#             */
/*   Updated: 2023/10/03 19:39:09 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
/*---------------------------------------------------------------------------/
/                                      index                                 /
/---------------------------------------------------------------------------*/
/*

Manipulation de la mémoire :

	ft_bzero	Met a zero les octets d'une chaine de character
	ft_memset	Remplir la mémoire avec un byte constant.
	ft_memcmp	Comparer les zones de mémoire.
	ft_memmove	Copier la zone de mémoire et deplace dans une autre
	ft_memcpy	Copier la zone de mémoire.
	ft_memchr	Rechercher un caractère dans la mémoire.
	ft_calloc	Alloue de la mémoire et fixe la valeur de ses octets à 0.

Manipulation de chaînes de caractères :

	ft_strlen		Calcule la longueur d'une chaîne de caractères.
	ft_strdup		Duplique la chaîne passée en paramètre.
	ft_strlcpy		Copier une string dans une taille spécifique.
	ft_strlcat		Concaténer une chaîne de caractères à une taille spécifique.
	ft_strncmp		Comparer deux chaînes de caractères sur une taille.
	ft_strchr		Localiser un caractère dans une chaîne de caractères.
	ft_strrchr		Localiser un caractère dans une chaîne de caractères.
	ft_strnstr		Localiser une sous-chaîne dans une chaîne de caractères.
	ft_substr		Renvoie une sous-chaîne d'une chaîne.
	ft_strjoin		Alloue et retourne une nouvelle string résultant de la 
						concaténation de 's1' suivi de 's2'.
	ft_striteri		Applique une fonction à chaque caractère d'une chaîne.
	ft_strmapi		Applique une fonction à chaque caractère d'une chaîne.
	ft_strtrim		Coupe le début et la fin de la chaîne avec un 
						ensemble spécifique de caractères.

Conversion de types :

	ft_tolower		Convertit le caractère en minuscules.
	ft_toupper		Convertit le caractère en majuscule.
	ft_atoi			Convertit une chaîne de caractères en un entier.
	ft_itoa			Convertit un nombre en une chaîne de caractères.

Vérification de caractères :

	ft_isalnum		Vérifie la présence d'un caractère alphanumérique.
	ft_isalpha		Vérifie la présence d'un caractère alphabétique.
	ft_isascii		vérifie si c correspond au jeu de caractères ASCII.
	ft_isdigit		Vérifie la présence d'un chiffre (0 à 9).
	ft_isprint		Vérifie la présence d'un caractère imprimable.

Manipulation de listes :

	ft_lstnew		Crée un nouvel élément de liste.
	ft_lstadd_front Ajoute un élément au début d'une liste.
	ft_lstsize		Compte le nombre d'éléments d'une liste.
	ft_lstlast		Renvoie le dernier élément de la liste.
	ft_lstadd_back	Ajoute un élément à la fin d'une liste.
	ft_lstclear		Supprime et libère la liste.
	ft_lstiter		Applique une fonction à chaque élément d'une liste.
	ft_lstmap		Applique une fonction à chaque élément d'une liste.

Entrée/Sortie :

	ft_pustr_fd		Envoyer une string vers un descripteur de fichier.
	ft_putnbr_fd	Envoyer un nombre à un descripteur de fichier.
	ft_putchar_fd	Envoyer un cchar à un descripteur de fichier.
	ft_putendl_fd	Envoyer une string vers un descripteur de fichier,
						suivie d'une nouvelle ligne.
	ft_split		Divise une string en utilisant un char (charsets).

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
** Default
*/
# include <stdlib.h>
# include <unistd.h>

/*
** Manipulation de la mémoire :
*/
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);

/*
** Manipulation de chaînes de caractères :
*/
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);

/*
** Conversion de types :
*/
int		ft_tolower(int i);
int		ft_toupper(int i);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

/*
** Vérification de caractères :
*/
int		ft_isalnum(int i);
int		ft_isalpha(int i);
int		ft_isascii(int i);
int		ft_isdigit(int i);
int		ft_isprint(int i);

/*
** Manipulation de listes :
*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*
** Entrée/Sortie :
*/
void	ft_putnbr_fd(int nb, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putstr_fd(char *str, int fd);
char	**ft_split(char const *s, char c);

#endif