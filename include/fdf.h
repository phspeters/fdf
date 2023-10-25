/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:53:05 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/25 18:37:38 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# define WIDTH 1080
# define HEIGHT 1920
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_pixel
{
	uint32_t		x_axis;
	uint32_t		y_axis;
	int32_t			z_axis;
	uint32_t		rgba_channel;
}					t_pixel;

// talvez fazer pixels com apenas uma direção?
typedef struct s_master
{
	mlx_t			*window;
	mlx_image_t		*image;
	unsigned int	map_height;
	unsigned int	map_width;
	t_pixel			**pixels;
}					t_master;

int					parse_args_and_map(int argc, char **argv, t_master *master);
t_pixel				**read_map(char *filename, int width, int height);
void				draw_map(t_master *master, int height, int width);
void				draw_line_bresenham(int x, int y, int x2, int y2, t_master *master);
#endif