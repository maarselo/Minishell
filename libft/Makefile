# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 16:51:09 by mvillavi          #+#    #+#              #
#    Updated: 2025/01/12 20:20:41 by mvillavi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER = libft.h

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
       ft_isspace.c ft_toupper.c ft_tolower.c ft_atoi.c ft_memcmp.c ft_strncmp.c \
       ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_itoa.c ft_strchr.c \
       ft_strdup.c ft_strrchr.c ft_calloc.c ft_strjoin.c ft_memmove.c \
       ft_strtrim.c ft_substr.c ft_strmapi.c ft_strnstr.c ft_putnbr_fd.c \
       ft_bzero.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_memset.c \
       ft_memchr.c ft_striteri.c ft_memcpy.c ft_split.c get_next_line.c get_next_line_bonus.c \
	   printf_utils.c printf.c

OBJS = $(SRCS:.c=.o)

BSRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BOBJS = $(BSRCS:.c=.o)

CC = cc
CC_LIB = ar -rcs
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) Makefile
	$(CC_LIB) $(NAME) $(OBJS)

bonus: $(OBJS) $(BOBJS)
	$(CC_LIB) $(NAME) $(BOBJS)

%.o:%.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

