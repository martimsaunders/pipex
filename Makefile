# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 16:34:39 by mprazere          #+#    #+#              #
#    Updated: 2025/06/26 13:21:16 by mprazere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT_DIR = ./libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
PIPEX_A = libpipex.a

SRCS = srcs/pipex.c srcs/p_error.c srcs/p_utils.c srcs/p_path.c \
srcs/p_here_doc.c srcs/p_ft_split.c srcs/p_utils_split.c \

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs

all: $(LIBFT) $(PIPEX_A) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(PIPEX_A): $(OBJS)
	@$(AR) $(PIPEX_A) $(OBJS)
	@echo 'Biblioteca libpipex.a criada!'

$(NAME): $(OBJS) $(MAIN)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo 'pipex compilado com libft!'

clean:
	@rm -f $(OBJS)
	@rm -f $(PIPEX_A)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo 'Objetos limpos!'

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo 'Tudo limpo!'

re: fclean all

.PHONY: all clean fclean re
