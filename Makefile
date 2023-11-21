# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 16:05:00 by pehenri2          #+#    #+#              #
#    Updated: 2023/11/21 17:47:34 by pehenri2         ###   ########.fr        #
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
SRCS		= 	01_main.c						\
				02_parse_args_and_map.c			\
				03_read_map.c					\
				04_camera.c						\
				05_projections.c				\
				06_transformation.c				\
				07_render.c						\
				08_draw_line.c					\
				09_color.c						\
				10_hooks.c						\
				11_utils.c						\
				12_error.c
OBJS		= $(addprefix $(SRCS_PATH),$(SRCS:%.c=%.o))
BONUS_PATH	= ./src/bonus/
BONUS_SRCS	= 	01_main_bonus.c					\
				02_parse_args_and_map_bonus.c	\
				03_read_map_bonus.c				\
				04_camera_bonus.c				\
				05_projections_bonus.c			\
				06_transformation_bonus.c		\
				07_render_bonus.c				\
				08_draw_line_bonus.c			\
				09_color_bonus.c				\
				10_hooks_bonus.c				\
				11_hooks_utils_bonus.c			\
				12_rotation_bonus.c				\
				13_utils_bonus.c				\
				14_error_bonus.c
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

norm:
	@norminette $(SRCS_PATH) $(BONUS_PATH) include

val: all
	valgrind --leak-check=full --suppressions=MLX42_suppressions ./fdf maps/42.fdf

valbonus: bonus
	valgrind --leak-check=full --suppressions=MLX42_suppressions ./fdf_bonus maps/42.fdf

.PHONY: all, clean, fclean, re, rebonus, norm, val, valbonus