/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:53:05 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/15 08:12:41 by pehenri2         ###   ########.fr       */
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

typedef struct s_camera
{
	float			proportion;
	float			zoom;
	int				x_offset;
	int				y_offset;
}					t_camera;

typedef struct s_pixel
{
	float			x_axis;
	float			y_axis;
	float			z_axis;
	uint32_t		rgba_channel;
}					t_pixel;

typedef struct s_map_info
{
	unsigned int	height;
	unsigned int	width;
	int				max_z;
	int				min_z;
}					t_map_info;

//trocar name para de pixels para map?
typedef struct s_map
{
	t_pixel			**pixels;
	int				x_max;
	int				x_min;
	int				y_max;
	int				y_min;
}					t_map;

typedef struct s_fdf
{
	mlx_t			*window;
	mlx_image_t		*image;
	t_camera		camera;
	t_map_info		map_info;
	t_map			parallel;
	t_map			isometric;
}					t_fdf;

int					parse_args_and_map(int argc, char **argv, t_fdf *fdf);
t_pixel				**read_map(char *filename, t_map_info *map_info);
void				draw_map(t_fdf *fdf, int height, int width);
void				draw_line_bresenham(t_pixel start, t_pixel end,
						t_fdf *fdf);
void				generic_key_hook(void *param);
t_pixel				to_isometric(t_pixel pixel);
t_pixel				apply_proportion(t_pixel pixel, float proportion);
t_line_info			get_x_and_y(t_pixel start, t_pixel end, t_fdf fdf);
void				put_valid_pixel(mlx_image_t *img, int x, int y,
						uint32_t color);
void				move_coordinate(int *coordinate, int direction);
void				init_camera_params(t_fdf *fdf);
// temp
void				print_map(t_pixel **pixels, int height, int width);
void				map_to_iso(t_pixel **pixels, int height, int width);

#endif