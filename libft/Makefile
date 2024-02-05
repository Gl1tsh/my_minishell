# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 19:39:17 by nagiorgi          #+#    #+#              #
#    Updated: 2024/02/05 16:22:17 by nagiorgi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Liste des fichiers source
SRCS = 	ft_strcmp.c \
		ft_atoi.c \
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
		ft_strndup.c \

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

# Couleurs
GREEN=\033[0;32m
RED=\033[0;31m
PURPLE=\033[0;35m
NC=\033[0m # No Color

.c.o:
	@printf "\r\033[K│ Compiling $<... "
	@$(CC) $(CFLAGS) -c $< -o $@ > temp.log 2>&1 || touch temp.err
	@if test -e temp.err; then \
		printf "${RED}Error${NC}     "; \
		rm temp.err; \
	elif grep -q "warning" temp.log; then \
		printf "${PURPLE}Warnings${NC}     "; \
	fi
	@rm -f temp.log

# Règle par défaut pour construire la bibliothèque
$(NAME): $(OBJS)
	@${ARC} $(NAME) $^
	@printf "\n"
	@printf "│${GREEN}\033[1m Success: Libft files compiled successfully.${NC}\033[0m\n"

all:	$(NAME)

clean:
	@${CLEAN} ${OBJS}

fclean:	clean
	@${CLEAN} ${NAME}

re:	fclean	all

bonus:		${OBJB}
	@${ARC} ${NAME} ${OBJB}
	@echo "Bonus added."