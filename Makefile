# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 16:05:00 by pehenri2          #+#    #+#              #
#    Updated: 2024/02/09 16:47:32 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
BONUS_NAME	= 	fdf_bonus
CFLAGS		=	-Wextra -Wall -Werror -Wunreachable-code $(FLAG)
FLAG 		?= 	-Ofast
LIBMLX		= 	./lib/MLX42
LIBFT		= 	./lib/libft
CC			= 	cc
HEADERS		= 	-I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS		= 	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
SRCS_PATH	= 	./src/mandatory/
SRCS		= 	camera.c					\
				color.c						\
				draw_line.c					\
				error.c						\
				hooks.c						\
				main.c						\
				parse_args_and_map.c		\
				projections.c				\
				read_map.c					\
				render.c					\
				transformation.c			\
				utils.c						
OBJS		=	 $(addprefix $(SRCS_PATH),$(SRCS:%.c=%.o))
BONUS_PATH	= 	./src/bonus/
BONUS_SRCS	= 	camera_bonus.c				\
				color_bonus.c				\
				draw_line_bonus.c			\
				error_bonus.c				\
				hooks_bonus.c				\
				hooks_utils_bonus.c			\
				main_bonus.c				\
				parse_args_and_map_bonus.c	\
				projections_bonus.c			\
				read_map_bonus.c			\
				render_bonus.c				\
				rotation_bonus.c			\
				transformation_bonus.c		\
				utils_bonus.c				
BONUS_OBJS	= 	$(addprefix $(BONUS_PATH), $(BONUS_SRCS:%.c=%.o))
EXE			?= 	fdf

all: libmlx libft $(NAME)

bonus: libmlx libft $(BONUS_NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT) --silent

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

val: all bonus
	valgrind --leak-check=full --suppressions=MLX42_suppressions ./$(EXE) maps/42.fdf

norm:
	@norminette $(SRCS_PATH) $(BONUS_PATH) include $(LIBFT)

.PHONY: all, clean, fclean, re, rebonus, norm, val