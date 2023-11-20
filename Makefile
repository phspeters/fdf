# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 16:05:00 by pehenri2          #+#    #+#              #
#    Updated: 2023/11/19 20:59:41 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= fdf
NAME_BONUS	:= fdf_bonus
CFLAGS		:= -Wextra -Wall -Werror -Wunreachable-code -g3
LIBMLX		:= ./lib/MLX42
LIBFT		:= ./lib/libft
CC			:= cc
HEADERS		:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS		:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
PATH		:= ./src/
SRCS		:= 	camera.c \
				draw_utils.c \
				draw.c \
				hooks.c \
				main.c \
				parse_args_and_map.c \
				projections.c \
				read_map.c \
				rotation.c
OBJS		:= ${addpreffix $(PATH), $(SRCS:%.c=%.o)}
PATH_BONUS	:= ./bonus/
SRCS_BONUS	:= 	camera.c \
				draw_utils.c \
				draw.c \
				hooks_bonus.c \
				main_bonus.c \
				parse_args_and_map.c \
				projections_bonus.c \
				read_map.c \
				rotation_bonus.c
OBJS_BONUS	:= ${addpreffix $(PATH_BONUS), $(SRCS_BONUS:%.c=%.o)}

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<\n)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

bonus: libmlx libft $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME_BONUS)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJS_BONUS)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@make -C $(LIBFT) fclean

re: fclean all

val:
	valgrind --leak-check=full --suppressions=suppressions ./fdf maps/42.fdf

.PHONY: all, clean, fclean, re, val