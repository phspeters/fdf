/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:53:05 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/20 21:02:04 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

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

typedef struct s_pixel
{
	float			x_axis;
	float			y_axis;
	float			z_axis;
	uint32_t		rgba_channel;
}					t_pixel;

typedef struct s_map
{
	t_pixel			**pixels;
	float			x_max;
	float			x_min;
	float			y_max;
	float			y_min;
	int				x_offset_correction;
	int				y_offset_correction;
}					t_map;

typedef struct s_map_info
{
	unsigned int	height;
	unsigned int	width;
	float			x_offset;
	float			y_offset;
	int				max_z;
	int				min_z;
	int32_t			background_color;
}					t_map_info;

typedef struct s_camera
{
	float			proportion;
	float			zoom;
	int				x_offset;
	int				y_offset;
	float			x_angle;
	float			y_angle;
	float			z_angle;
}					t_camera;

typedef struct s_fdf
{
	mlx_t			*window;
	mlx_image_t		*image;
	t_camera		camera;
	t_map_info		map_info;
	t_map			parallel;
	t_map			isometric;
	t_map			oblique;
	t_map			*current_map;
}					t_fdf;

//1_main_bonus.c
void			draw_loop(void *param);
void			action_hooks(void *param);

//2_parse_args_and_map.c
int				parse_args_and_map(int argc, char **argv, t_fdf *fdf);
int				parse_args(int argc, char *argv);
unsigned int	get_width(char *line);
unsigned int	get_height_and_check_width(int fd, unsigned int map_width);

//3_read_map.c
t_pixel			**read_map(char *filename, t_map_info *map_info);
char			**get_coordinates_from_line(int fd);
void			populate_pixel_matrix(t_pixel *pixel, char *str, int h, int w);
uint32_t		get_color(char *coordinate);
void			refresh_min_and_max_z(int z_axis, t_map_info *map_info);

//4_camera.c
void			init_camera_and_map_params(t_fdf *fdf);
int				get_map_proportion(t_map_info map_info);
void			apply_camera_params(t_map *map, t_map_info map_info, t_camera cam);
void			centralize_pixel(t_pixel *pixel, t_map_info map_info);
void			apply_proportion(t_pixel *pixel, t_camera cam);

//5_projections_bonus
void			init_map_projections(t_fdf *fdf);
void			init_map(t_map *map, t_fdf fdf);
void			transform_map(t_map *map, t_fdf *fdf, void (*func)(t_pixel *));
void			set_initial_zoom(t_map *map, float *zoom);
void			set_map_offset_correction(t_map *map);

//6_transformation_bonus.c
void			to_isometric(t_pixel *pixel);
void			to_oblique(t_pixel *pixel);

//7_render_bonus.c
void			render_image(t_map *map, t_map_info map_info, t_fdf *fdf);
void			render_background(t_fdf *fdf);

//8_draw_line.c
void			draw_line(t_pixel start, t_pixel end, t_fdf *fdf);
t_line_info		set_line_info(t_pixel start, t_pixel end, t_camera cam, t_map *map);
t_line_info		get_line_coordinates(t_pixel start, t_pixel end, t_camera camera, t_map map);
void			draw_line_closer_to_x_axis(t_line_info line_info, mlx_image_t *image);
void			draw_line_closer_to_y_axis(t_line_info line_info, mlx_image_t *image);

//9_hooks_bonus.c
void			translate_loop_hook(void *param);
void			rotate_loop_hook(void *param);
void			rotate_key_hook(mlx_key_data_t keydata, void *param);
void			zoom_loop_hook(void *param);
void			zoom_scroll_hook(double xdelta, double ydelta, void *param);

//10_hooks_utils_bonus.c
void			select_projection_loop_hook(void *param);
void			reset_position_loop_hook(void *param);
void			close_loop_hook(void *param);

//11_rotation_bonus.c
void			rotate_pixel(t_pixel *pixel, t_camera cam);
void			rotate_around_x_axis(t_pixel *pixel, float angle);
void			rotate_around_y_axis(t_pixel *pixel, float angle);
void			rotate_around_z_axis(t_pixel *pixel, float angle);

//12_utils_bonus.c
void			put_valid_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void			move_coordinate(int *coordinate, int direction);
void			refresh_corner_pixels(t_pixel pixel, t_map *map);
void			free_maps(t_fdf *fdf);

//13_error.c
void			handle_mlx_error(t_fdf *fdf);

#endif