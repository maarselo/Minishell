# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/29 15:39:24 by fbanzo-s          #+#    #+#              #
#    Updated: 2025/06/30 20:26:47 by fbanzo-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
#BONUS = minishell_bonus

SRC_DIR = src
#BONUS_DIR = bonus
OBJ_DIR = obj
#OBJ_BONUS_DIR = obj_bonus
INCLUDE_DIR = include
LIBFT_DIR = ./Libft

HEADER = includes/minishell.h
#BONUS_HEADER = $(INCLUDE_DIR)/minishell_bonus.h

SRCS_FILES = minishell.c
#BONUS_FILES = 

SRCS = $(addprefix $(SRC_DIR)/, $(SRCS_FILES))
#BSRCS = $(addprefix $(BONUS_DIR)/, $(BONUS_FILES))

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))
#OBJS_BONUS = $(addprefix $(OBJ_BONUS_DIR)/, $(BONUS_FILES:.c=.o))

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I$(INCLUDE_DIR)
LIB_FLAGS = -lreadline -lft 
# -fsanitize=address
RM = rm -rf

GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m
BULLET = $(BLUE)•$(RESET)
BULLET_RED = $(RED)•$(RESET)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR) -Iincludes

all: $(NAME)

$(LIBFT):
	@make -sC $(LIBFT_DIR)
	@make -sC $(LIBFT_DIR) bonus

$(NAME): $(OBJS) $(LIBFT) $(HEADER) Makefile
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) $(LIB_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ Compilación completada!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)▶ Compilando $(RESET) $<..."

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BULLET) $(BLUE)Created:$(RESET) $(OBJ_DIR)/"

clean:
	@echo "$(BULLET_RED) $(RED)Cleaning:$(RESET) object files"
	@make -sC $(LIBFT_DIR) clean 
	@$(RM) $(OBJ_DIR) 
#   $(OBJ_BONUS_DIR)

fclean: clean
	@echo "$(BULLET_RED) $(RED)Removing:$(RESET) $(NAME)"
	@make -sC $(LIBFT_DIR) fclean
	@rm -f $(NAME) 
#$(BONUS)

re: fclean all

.PHONY: all clean fclean re
#bonus