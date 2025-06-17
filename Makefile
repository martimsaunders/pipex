# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: praders <praders@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 16:34:39 by mprazere          #+#    #+#              #
#    Updated: 2025/06/17 17:50:48 by praders          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT_DIR = ./libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
PIPEX_A = libpipex.a

SRCS = srcs/pipex.c srcs/p_error.c srcs/p_utils.c #srcs/p_path.c  \

OBJS = $(SRCS:.c=.o)

BONUS_SRCS = 

BONUS_OBJS = $(BONUS_SRCS:.c=.o)
BONUS_MAIN = srcs_bonus/main_bonus.c

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

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -L$(LIBFT_DIR) -lft -o $(BONUS_NAME)
	@echo 'pipex_bonus compilado com libft!'

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)
	@rm -f $(PIPEX_A)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo 'Objetos limpos!'

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo 'Tudo limpo!'

re: fclean all

.PHONY: all clean fclean re bonus
