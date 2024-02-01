B = $(shell tput bold)
VERT = $(shell tput setaf 2)
BLEU = $(shell tput setaf 4)
D = $(shell tput sgr0)

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -g -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline
BUILDDIR = build/

LIBFT = libft/libft.a

SRCS = $(shell find src -name '*.c')
OBJS = $(patsubst src/%.c,$(BUILDDIR)%.o,$(SRCS))
INCLUDES = -I./include -I./libft

# Total number of source files
TOTAL_FILES = $(words $(SRCS))

# Counter for progress
COUNT = 0

# Function to update the progress bar
define update_progress
    @$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
    @printf "\r$(B)Compiling $(NAME): ["
    @i=0; while [[ $$i -lt $(COUNT) ]]; do printf "$(VERT)█$(D)"; ((i = i + 1)); done
    @i=$(COUNT); while [[ $$i -lt $(TOTAL_FILES) ]]; do printf " "; ((i = i + 1)); done
    @percentage=$$(( 100 * $(COUNT) / $(TOTAL_FILES) )); \
    printf "] %d%%" "$$percentage"
endef

all: $(NAME)
	@printf "\n$(B)$(BLEU) -------------- $(NAME) compiled successfully --------------$(D)\n\n"

$(LIBFT):
	@make -C libft

$(BUILDDIR)%.o: src/%.c
	@mkdir -p $(BUILDDIR)builtins
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@$(call update_progress)

$(NAME): $(LIBFT) $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

clean:
	@make -C libft clean
	@echo "Cleaning $(NAME)\n"
	@rm -rf $(BUILDDIR)

fclean:
	@make -C libft fclean
	@echo "Deep cleaning $(NAME)\n"
	@rm -rf $(BUILDDIR) $(NAME)

re: fclean all