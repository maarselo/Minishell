# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/29 15:39:24 by fbanzo-s          #+#    #+#              #
#    Updated: 2025/06/29 17:14:54 by fbanzo-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
RESET   = \033[0m

NAME = minishell
HEADER = includes/minishell.h

CC = cc
CFLAGS = -Wall -Wextra -Werror
# -fsanitize=address

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
INCLUDES = -I$(LIBFT_DIR) -Iincludes

SRC_DIR = src
OBJ_DIR = $(SRC_DIR)/obj

SRCS = minishell.c

SRC = $(addprefix $(SRC_DIR)/, $(SRCS))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: libft $(NAME)

libft:
	@make -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ) Makefile
	@echo "$(YELLOW)Compilando $@...$(RESET)"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Hecho$(RESET)"

clean:
	@echo "$(RED)Limpiando objetos...$(RESET)"
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Limpiando todo...$(RESET)"
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re