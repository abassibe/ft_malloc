# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abassibe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 12:45:46 by abassibe          #+#    #+#              #
#    Updated: 2018/06/06 03:07:42 by abassibe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
		HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRCS =	malloc.c \
		free.c \
		realloc.c \
		calloc.c \
		show_alloc_mem.c \
		new_allocation.c \
		first_allocation.c \
		utils.c

OBJS = $(SRCS:.c=.o)

SRCPATH = ./srcs/

FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@gcc -shared $(FLAGS) $(OBJS) libft/libft.a -o $(NAME)
	@ln -sf $(NAME) libft_malloc.so

%.o: $(SRCPATH)%.c
	@gcc $(FLAGS) -fPIC -o $@ -c $<

.PHONY: all clean fclean re

clean:
	@make -C libft clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C libft fclean
	@rm -rf libft/libft.a $(NAME)

re: fclean all
