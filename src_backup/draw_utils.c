/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:29:45 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/08 14:20:24 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_valid_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if ((x > 0 && x < WIDTH) && (y > 0 && y < HEIGHT))
		mlx_put_pixel(img, x, y, color);
}

void	move_coordinate(int *coordinate, int direction)
{
	if (direction < 0)
		*coordinate -= 1;
	else
		*coordinate += 1;
}

t_pixel	apply_distance(t_pixel pixel, float pixel_distance)
{
	t_pixel	spaced_pixel;

	spaced_pixel.x_axis = pixel.x_axis * pixel_distance;
	spaced_pixel.y_axis = pixel.y_axis * pixel_distance;
	spaced_pixel.z_axis = pixel.z_axis * pixel_distance * 0.25;
	spaced_pixel.rgba_channel = pixel.rgba_channel;
	return (spaced_pixel);
}

t_line_info	get_x_and_y(t_pixel start, t_pixel end, t_master master)
{
	t_line_info	line_info;

	line_info.x1 = start.x_axis + master.x_offset;
	line_info.y1 = start.y_axis + master.y_offset;
	line_info.x2 = end.x_axis + master.x_offset;
	line_info.y2 = end.y_axis + master.y_offset;
	return (line_info);
}

t_pixel	to_isometric(t_pixel pixel)
{
	t_pixel	new_pixel;
	float	angle;

	angle = 30 * (M_PI / 180);
	new_pixel.x_axis = (pixel.x_axis - pixel.y_axis) * cos(angle);
	new_pixel.y_axis = (pixel.x_axis + pixel.y_axis) * sin(angle)
		- (pixel.z_axis);
	new_pixel.z_axis = pixel.z_axis;
	new_pixel.rgba_channel = pixel.rgba_channel;
	return (new_pixel);
}
