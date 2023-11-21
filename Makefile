# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 16:05:00 by pehenri2          #+#    #+#              #
#    Updated: 2023/11/21 13:02:30 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
BONUS_NAME	= fdf_bonus
CFLAGS		= -Wextra -Wall -Werror -Wunreachable-code -lm -g3 #-Ofast
LIBMLX		= ./lib/MLX42
LIBFT		= ./lib/libft
CC			= cc
HEADERS		= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS		= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
SRCS_PATH	= ./src/mandatory/
SRCS		= 	camera.c				\
				draw_utils.c			\
				draw.c					\
				hooks.c					\
				main.c					\
				parse_args_and_map.c	\
				projections.c			\
				read_map.c				\
				rotation.c
OBJS		= $(addprefix $(SRCS_PATH),$(SRCS:%.c=%.o))
BONUS_PATH	= ./src/bonus/
BONUS_SRCS	= 	1_main_bonus.c				\
				2_parse_args_and_map.c		\
				3_read_map.c				\
				4_camera.c					\
				5_projections_bonus.c		\
				6_transformation_bonus.c	\
				7_render_bonus.c			\
				8_draw_line.c				\
				9_hooks_bonus.c				\
				10_hooks_utils_bonus.c		\
				11_rotation_bonus.c			\
				12_utils_bonus.c			\
				13_error.c
BONUS_OBJS	= $(addprefix $(BONUS_PATH), $(BONUS_SRCS:%.c=%.o))

all: libmlx libft $(NAME)

bonus: libmlx libft $(BONUS_NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<\n)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBS) $(HEADERS) -o $(BONUS_NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(BONUS_OBJS)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS_NAME)
	@make -C $(LIBFT) fclean

re: fclean all

rebonus: fclean bonus

val:
	valgrind --leak-check=full --suppressions=MLX42_suppressions ./fdf_bonus maps/42.fdf

.PHONY: all, clean, fclean, re, rebonus, val