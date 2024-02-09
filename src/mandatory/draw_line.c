/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:49:23 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/08 10:04:04 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Receives two pixels and draws a line between them. The line is drawn
 * using the Bresenham's line algorithm. The color of the line is interpolated
 * between the start and end pixels.
 * 
 * @param start Pixel that represents the start of the line. 
 * @param end Pixel that represents the end of the line.
 * @param fdf Struct that contains the information about the current map and the
 * camera parameters.
 */
void	draw_line(t_pixel start, t_pixel end, t_fdf *fdf)
{
	t_line_info	line_info;

	line_info = set_line_info(start, end, fdf->camera, fdf->current_map);
	if (line_info.abs_dx > line_info.abs_dy)
		draw_shallow_line(line_info, fdf->image);
	else
		draw_steep_line(line_info, fdf->image);
}

/**
 * @brief Function that sets the line information needed to draw the line and
 * stores it in the line_info struct.
 *  
 * @param start Pixel that represents the start of the line. 
 * @param end Pixel that represents the end of the line.
 * @param cam Camera struct that contains the current camera parameters.
 * @param map Current map that is being drawn.
 * @return t_line_info that contains the information needed to draw the line. 
 */
t_line_info	set_line_info(t_pixel start, t_pixel end, t_camera cam, t_map *map)
{
	t_line_info	line_info;

	line_info = get_line_coordinates(start, end, cam, *map);
	line_info.dx = line_info.x2 - line_info.x1;
	line_info.dy = line_info.y2 - line_info.y1;
	line_info.abs_dx = abs(line_info.dx);
	line_info.abs_dy = abs(line_info.dy);
	line_info.start_color = start.rgba_channel;
	line_info.end_color = end.rgba_channel;
	return (line_info);
}

/**
 * @brief Function that calculates the start and end coordinates of the line
 * in the window based on the camera parameters and the map.
 * 
 * @param start Pixel that represents the start of the line. 
 * @param end Pixel that represents the end of the line.
 * @param camera Camera struct that contains the current camera parameters.
 * @param map Current map that is being drawn.
 * @return t_line_info that contains the information needed to draw the line. 
 */
t_line_info	get_line_coordinates(t_pixel start, t_pixel end, t_camera camera,
	t_map map)
{
	t_line_info	line_info;

	start.x_axis = ((start.x_axis - map.x_offset_correction) * camera.zoom)
		+ camera.x_offset;
	start.y_axis = ((start.y_axis - map.y_offset_correction) * camera.zoom)
		+ camera.y_offset;
	end.x_axis = ((end.x_axis - map.x_offset_correction) * camera.zoom)
		+ camera.x_offset;
	end.y_axis = ((end.y_axis - map.y_offset_correction) * camera.zoom)
		+ camera.y_offset;
	line_info.x1 = start.x_axis;
	line_info.y1 = start.y_axis;
	line_info.x2 = end.x_axis;
	line_info.y2 = end.y_axis;
	return (line_info);
}

/**
 * @brief Function that uses the Bresenham's line algortihm to draw a line
 * between two pixels that are more horizontally distant from each other than
 * they are vertically distant. That is, the absolute value of the difference
 * between the x coordinates of the two pixels is greater than the absolute
 * value of the difference between the y coordinates of the two pixels.
 * 
 * @param line_info Struct that contains the information needed to draw the line.
 * @param image Struct that contains the pointer to the image that is being
 * drawn into.
 */
void	draw_shallow_line(t_line_info line_info, mlx_image_t *image)
{
	int				decision;
	unsigned int	i;

	put_valid_pixel(image, line_info.x1, line_info.y1, line_info.start_color);
	decision = 2 * line_info.abs_dy - line_info.abs_dx;
	i = 0;
	while (i < line_info.abs_dx)
	{
		move_coordinate(&line_info.x1, line_info.dx);
		if (decision < 0)
			decision = decision + 2 * line_info.abs_dy;
		else
		{
			move_coordinate(&line_info.y1, line_info.dy);
			decision = decision + (2 * line_info.abs_dy - 2 * line_info.abs_dx);
		}
		put_valid_pixel(image, line_info.x1, line_info.y1,
			interpolate_color(line_info.start_color, line_info.end_color,
				(float)i / line_info.abs_dx));
		i++;
	}
}

/**
 * @brief Function that uses the Bresenham's line algortihm to draw a line
 * between two pixels that are more vertically distant from each other than
 * they are horizontally distant. That is, the absolute value of the difference
 * between the y coordinates of the two pixels is greater than the absolute
 * value of the difference between the x coordinates of the two pixels.
 * 
 * @param line_info Struct that contains the information needed to draw the line.
 * @param image Struct that contains the pointer to the image that is being
 * drawn into.
 */
void	draw_steep_line(t_line_info line_info, mlx_image_t *image)
{
	int				decision;
	unsigned int	i;

	put_valid_pixel(image, line_info.x1, line_info.y1, line_info.start_color);
	decision = 2 * line_info.abs_dx - line_info.abs_dy;
	i = 0;
	while (i < line_info.abs_dy)
	{
		move_coordinate(&line_info.y1, line_info.dy);
		if (decision < 0)
			decision = decision + 2 * line_info.abs_dx;
		else
		{
			move_coordinate(&line_info.x1, line_info.dx);
			decision = decision + (2 * line_info.abs_dx - 2 * line_info.abs_dy);
		}
		put_valid_pixel(image, line_info.x1, line_info.y1,
			interpolate_color(line_info.start_color, line_info.end_color,
				(float)i / line_info.abs_dy));
		i++;
	}
}
