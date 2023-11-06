# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 16:05:00 by pehenri2          #+#    #+#              #
#    Updated: 2023/11/06 16:29:04 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#colocar nome dos arquivos nomeados
NAME	:= fdf
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -g3
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<\n)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx,