/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:53:05 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/07 14:41:54 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <errno.h>
# define WIDTH 1600
# define HEIGHT 900
# define MENU_WIDTH 330
# define MENU_HEIGHT 260

/**
 * @brief Struct that holds the information needed to draw a line between two
 * pixels (x1,y1) and (x2,y2) using the Bresenham's Line Algorithm.
 * 
 * @param x1 The x coordinate of the first pixel.
 * @param y1 The y coordinate of the first pixel.
 * @param x2 The x coordinate of the second pixel.
 * @param y2 The y coordinate of the second pixel.
 * @param dx The difference between the x coordinates of the two pixels.
 * @param dy The difference between the y coordinates of the two pixels.
 * @param abs_dx The absolute value of the difference between the x coordinates
 * of the two pixels.
 * @param abs_dy The absolute value of the difference between the y coordinates
 * of the two pixels.
 * @param start_color The color of the first pixel.
 * @param end_color The color of the second pixel.
 */
typedef struct s_line_info
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				dx;
	int				dy;
	unsigned int	abs_dx;
	unsigned int	abs_dy;
	uint32_t		start_color;
	uint32_t		end_color;
}					t_line_info;

/**
 * @brief Struct that holds the information of a pixel in the map.
 * 
 * @param x_axis The x coordinate of the pixel.
 * @param y_axis The y coordinate of the pixel.
 * @param z_axis The z coordinate of the pixel.
 * @param rgba_channel The color of the pixel in the format 0xRRGGBBAA.
 */
typedef struct s_pixel
{
	float			x_axis;
	float			y_axis;
	float			z_axis;
	uint32_t		rgba_channel;
}					t_pixel;

/**
 * @brief Struct that holds the information of the map passed as argument to the
 * fdf program.
 * 
 * @param pixels The matrix of pixels that represents the map.
 * @param x_max The maximum x coordinate of the map.
 * @param x_min The minimum x coordinate of the map.
 * @param y_max The maximum y coordinate of the map.
 * @param y_min The minimum y coordinate of the map.
 * @param x_offset_correction The correction to the x offset of the map.
 * @param y_offset_correction The correction to the y offset of the map.
 */
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

/**
 * @brief Struct that holds the information of the map.
 * 
 * @param height The height of the map.
 * @param width The width of the map.
 * @param x_offset The x offset of the map.
 * @param y_offset The y offset of the map.
 * @param max_z The maximum z coordinate of the map.
 * @param min_z The minimum z coordinate of the map.
 * @param background_color The color of the background of the map.
 */
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

/**
 * @brief Struct that holds the information of the camera.
 * 
 * @param proportion The proportion of the map.
 * @param zoom The zoom of the map.
 * @param x_offset The x offset of the camera.
 * @param y_offset The y offset of the camera.
 * @param x_angle The angle of rotation around the x axis.
 * @param y_angle The angle of rotation around the y axis.
 * @param z_angle The angle of rotation around the z axis.
 */
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

/**
 * @brief Struct that holds the information of the fdf program.
 * 
 * @param window The window pointer.
 * @param image The image pointer.
 * @param camera The camera struct.
 * @param map_info The map_info struct.
 * @param parallel The map information in parallel projection.
 * @param isometric The map information in isometric projection.
 * @param oblique The map information in oblique projection.
 * @param current_map Pointer to the current map. Either parallel or isometric.
 */
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

//01_main_bonus.c

void			draw_loop(void *param);
void			action_hooks(void *param);

//02_parse_args_and_map.c

int				parse_args_and_map(int argc, char **argv, t_fdf *fdf);
int				parse_args(int argc, char *argv);
unsigned int	get_width(char *line);
unsigned int	get_height_and_check_width(int fd, unsigned int map_width);

//03_read_map.c

t_pixel			**read_map(char *filename, t_map_info *map_info);
void			populate_line(t_pixel **map, t_map_info *map_info, int fd,
					int h);
char			**get_coordinates_from_line(int fd);
void			populate_pixel_matrix(t_pixel *pixel, char *str, int h, int w);
uint32_t		get_color(char *coordinate);

//04_camera.c

void			init_camera_and_map_params(t_fdf *fdf);
int				get_map_proportion(t_map_info map_info);
void			apply_camera_params(t_map *map, t_map_info map_info,
					t_camera cam);
void			centralize_pixel(t_pixel *pixel, t_map_info map_info);
void			apply_proportion(t_pixel *pixel, t_camera cam);

//05_projections_bonus

void			init_map_projections(t_fdf *fdf);
void			init_map(t_map *map, t_fdf fdf);
void			transform_map(t_map *map, t_fdf *fdf, void (*func)(t_pixel *));
void			set_initial_zoom(t_map *map, float *zoom);
void			set_map_offset_correction(t_map *map);

//06_transformation_bonus.c

void			to_isometric(t_pixel *pixel);
void			to_oblique(t_pixel *pixel);
void			to_parallel(t_pixel *pixel);

//07_render_bonus.c

void			render_image(t_map *map, t_map_info map_info, t_fdf *fdf);
void			render_background(t_fdf *fdf);
void			render_controls_menu(t_fdf *fdf);
void			print_controls_on_the_screen(t_fdf *fdf);

//08_draw_line.c

void			draw_line(t_pixel start, t_pixel end, t_fdf *fdf);
t_line_info		set_line_info(t_pixel start, t_pixel end, t_camera cam,
					t_map *map);
t_line_info		get_line_coordinates(t_pixel start, t_pixel end,
					t_camera camera, t_map map);
void			draw_line_closer_to_x_axis(t_line_info line_info,
					mlx_image_t *image);
void			draw_line_closer_to_y_axis(t_line_info line_info,
					mlx_image_t *image);

//09_color.c

uint32_t		interpolate_color(uint32_t color1, uint32_t color2,
					float percentage);

//10_hooks_bonus.c

void			translate_loop_hook(void *param);
void			rotate_loop_hook(void *param);
void			rotate_key_hook(mlx_key_data_t keydata, void *param);
void			zoom_loop_hook(void *param);
void			zoom_scroll_hook(double xdelta, double ydelta, void *param);

//11_hooks_utils_bonus.c

void			select_projection_loop_hook(void *param);
void			reset_position_loop_hook(void *param);
void			background_color_loop_hook(void *param);
void			close_loop_hook(void *param);

//12_rotation_bonus.c

void			rotate_pixel(t_pixel *pixel, t_camera cam);
void			rotate_around_x_axis(t_pixel *pixel, float angle);
void			rotate_around_y_axis(t_pixel *pixel, float angle);
void			rotate_around_z_axis(t_pixel *pixel, float angle);

//13_utils_bonus.c

void			put_valid_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void			move_coordinate(int *coordinate, int direction);
void			refresh_corner_pixels(t_pixel pixel, t_map *map);
void			refresh_min_and_max_z(int z_axis, t_map_info *map_info);
void			free_maps(t_fdf *fdf);

//14_error.c

void			handle_mlx_error(t_fdf *fdf);
void			handle_error(char *message);

#endif