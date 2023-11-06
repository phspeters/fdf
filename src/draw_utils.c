/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:29:45 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/06 16:31:15 by pehenri2         ###   ########.fr       */
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

t_pixel	apply_zoom(t_pixel pixel, int zoom)
{
	t_pixel	zoomed_pixel;

	zoomed_pixel.x_axis = pixel.x_axis * zoom;
	zoomed_pixel.y_axis = pixel.y_axis * zoom;
	zoomed_pixel.z_axis = pixel.z_axis * zoom;
	zoomed_pixel.rgba_channel = pixel.rgba_channel;
	return (zoomed_pixel);
}

t_line_info	apply_offset(t_pixel start, t_pixel end, t_master master)
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
	new_pixel.x_axis = round((pixel.x_axis - pixel.y_axis) * cos(angle));
	new_pixel.y_axis = round((pixel.x_axis + pixel.y_axis) * sin(angle)
			- (pixel.z_axis));
	new_pixel.z_axis = pixel.z_axis;
	new_pixel.rgba_channel = pixel.rgba_channel;
	return (new_pixel);
}
