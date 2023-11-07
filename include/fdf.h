/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:53:05 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/07 16:30:52 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define WIDTH 1600
# define HEIGHT 900
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_line_info
{
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	int				dx;
	int				dy;
	unsigned int	abs_dx;
	unsigned int	abs_dy;
	uint32_t		start_color;
	uint32_t		end_color;
}					t_line_info;

typedef struct s_pixel
{
	int				x_axis;
	int				y_axis;
	int32_t			z_axis;
	uint32_t		rgba_channel;
}					t_pixel;

typedef struct s_master
{
	mlx_t			*window;
	mlx_image_t		*image;
	unsigned int	map_height;
	unsigned int	map_width;
	unsigned int	pixel_distance;
	int				x_offset;
	int				y_offset;
	t_pixel			**pixels;
}					t_master;

int					parse_args_and_map(int argc, char **argv, t_master *master);
t_pixel				**read_map(char *filename, int width, int height);
void				draw_map(t_master *master, int height, int width);
void				draw_line_bresenham(t_pixel start, t_pixel end,
						t_master *master);
void				generic_key_hook(void *param);
t_pixel				to_isometric(t_pixel pixel);
t_pixel				apply_distance(t_pixel pixel, int pixel_distance);
t_line_info			get_x_and_y(t_pixel start, t_pixel end, t_master master);
void				put_valid_pixel(mlx_image_t *img, int x, int y,
						uint32_t color);
void				move_coordinate(int *coordinate, int direction);
void				init_camera(t_master *master);
// temp
void				print_map(t_pixel **pixels, int height, int width);
void				map_to_iso(t_pixel **pixels, int height, int width);

#endif