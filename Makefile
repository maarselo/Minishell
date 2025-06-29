# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/29 15:39:24 by fbanzo-s          #+#    #+#              #
#    Updated: 2025/06/29 15:46:26 by fbanzo-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

OBJ	= $(SRCS:.c=.o)

asdfasdf

all:	libft pipex

libft:
	make -C $(LIBFT_DIR)
	@echo "\033[0;32mLibft se ha compilado correctamente.\033[0m"
	
pipex: $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBFT_FLAGS)
	@echo "\033[0;32mPipex se ha compilado.\033[0m"
	
%.o:%.c	Makefile pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f pipex
	make -C $(LIBFT_DIR) fclean

re:	fclean all

.PHONY:	all libft clean fclean re libft
