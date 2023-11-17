/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:53:05 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/16 20:14:18 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <libft.h>
# include <limits.h>
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
	float			x_offset;
	float			y_offset;
	float			x_angle;
	float			y_angle;
	float			z_angle;
	int				max_z;
	int				min_z;
}					t_map_info;

// trocar name para de pixels para map?
typedef struct s_map
{
	t_pixel			**pixels;
	float			x_max;
	float			x_min;
	float			y_max;
	float			y_min;
	int				x_offset;
	int				y_offset;
}					t_map;

typedef struct s_fdf
{
	mlx_t			*window;
	mlx_image_t		*image;
	t_camera		camera;
	t_map_info		map_info;
	t_map			parallel;
	t_map			isometric;
	t_map			*current_map;
}					t_fdf;

int					parse_args_and_map(int argc, char **argv, t_fdf *fdf);
t_pixel				**read_map(char *filename, t_map_info *map_info);
void				draw_map(t_map *map, t_map_info map_info, t_fdf *fdf);
void				draw_line_bresenham(t_pixel start, t_pixel end, t_fdf *fdf);
void				generic_key_hook(void *param);
void				to_isometric(t_pixel *pixel);
void				apply_proportion(t_pixel *pixel, float proportion);
t_line_info			get_x_and_y(t_pixel start, t_pixel end, t_camera camera, t_map map);
void				put_valid_pixel(mlx_image_t *img, int x, int y,
						uint32_t color);
void				move_coordinate(int *coordinate, int direction);
void				init_camera_and_map_params(t_fdf *fdf);
void				apply_camera_params(t_map *map, t_map_info map_info,
						t_camera camera);
void				init_projections(t_fdf *fdf);
void				refresh_corner_pixels(t_pixel pixel, t_map *map);
void				rotate_around_x_axis(t_pixel *pixel, float angle);
void				rotate_around_y_axis(t_pixel *pixel, float angle);
void				rotate_around_z_axis(t_pixel *pixel, float angle);
void				to_oblique(t_pixel *pixel);
void				to_isometric(t_pixel *pixel);
// temp
void				print_map(t_pixel **pixels, int height, int width);
void				map_to_iso(t_pixel **pixels, int height, int width);
void				print_pixel(t_pixel pixel);
#endif