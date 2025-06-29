# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/29 15:39:24 by fbanzo-s          #+#    #+#              #
#    Updated: 2025/06/29 15:43:56 by fbanzo-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f pipex
	make -C $(LIBFT_DIR) fclean

re:	fclean all

.PHONY:	all libft clean fclean re libft
