# ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ #
#   M I N I S H E L L   M A K E F I L E  #
# ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ #

NAME = minishell

ENTRY_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

HEADER = $(INCLUDE_DIR)/philosophers.h

SRC_FILES = main.c entry.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

CC = cc -g
CFLAGS = -Wall -Werror -Wextra -pthread -I$(INCLUDE_DIR) 
RM = rm -rf

GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m
BULLET = $(BLUE)•$(RESET)

all: $(NAME)

libft:
	make -p Li
$(NAME): $(OBJS) $(HEADER) Makefile
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ Compilación completada!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)▶ Compilando $(RESET) $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BULLET) $(BLUE)Created:$(RESET) $(OBJ_DIR)/"

clean:
	@echo "$(BULLET) $(RED)Cleaning:$(RESET) object files"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(BULLET) $(RED)Removing:$(RESET) $(NAME)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
