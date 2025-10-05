# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 18:23:58 by fbanzo-s          #+#    #+#              #
#    Updated: 2025/01/05 18:23:58 by fbanzo-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
RESET   = \033[0m

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_calloc.c ft_isspace.c \
ft_isdigit.c ft_isprint.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strcmp.c \
ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
ft_tolower.c ft_toupper.c ft_memset.c ft_bzero.c ft_memchr.c \
ft_memcpy.c ft_memcmp.c ft_memmove.c ft_substr.c ft_strjoin.c \
ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strndup.c \
ft_is_all_asnum.c ft_contains_metachar.c ft_isnumbers.c

SRC_GNL = get_next_line.c get_next_line_utils.c

SRC_PRINTF = ft_printf.c ft_putchar_p.c ft_putstr_p.c ft_putnbr_p.c \
ft_puthex_fd.c ft_putptr_fd.c ft_printf_fd.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstsize.c \
ft_lstlast.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ_DIR = obj

SRC_OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o)) $(addprefix $(OBJ_DIR)/,$(SRC_PRINTF:.c=.o)) $(addprefix $(OBJ_DIR)/,$(SRC_GNL:.c=.o))
BONUS_OBJ = $(addprefix $(OBJ_DIR)/,$(BONUS:.c=.o))

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRC_OBJ) Makefile
	ar rcs $(NAME) $(SRC_OBJ)

bonus: $(SRC_OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(BONUS_OBJ)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re