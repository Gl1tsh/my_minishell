# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 19:39:17 by nagiorgi          #+#    #+#              #
#    Updated: 2024/01/23 17:17:30 by nagiorgi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Liste des fichiers source
SRCS = 	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_memset.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_strrchr.c \
		ft_substr.c \
		ft_strtrim.c \
		ft_striteri.c \
		ft_strmapi.c \

SRCS_BONUS = 		ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstsize.c \
					ft_lstlast.c \
					ft_lstadd_back.c \
					ft_lstdelone.c \
					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c \

# Liste des fichiers objets
OBJS = $(SRCS:.c=.o)

OBJB = ${SRCS_BONUS:.c=.o}

# Nom du fichier d'en-tête
HEAD = libft.h

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Werror -Wextra -I.

# Nom de la bibliothèque
NAME = libft.a

CLEAN = rm -f

ARC = ar rcs

# Règle de compilation des fichiers source en fichiers objets
.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

# Règle par défaut pour construire la bibliothèque
$(NAME): $(OBJS)
	@${ARC} $(NAME) $^

all:	$(NAME)

clean:
	@${CLEAN} ${OBJS}

fclean:	clean
	@${CLEAN} ${NAME}

re:	fclean	all

bonus:		${OBJB}
	@${ARC} ${NAME} ${OBJB}
	@echo "Bonus added."
