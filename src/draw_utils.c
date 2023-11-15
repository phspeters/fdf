/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:29:45 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/15 08:53:57 by pehenri2         ###   ########.fr       */
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

t_pixel	apply_proportion(t_pixel pixel, float proportion)
{
	t_pixel	spaced_pixel;

	spaced_pixel.x_axis = pixel.x_axis * proportion;
	spaced_pixel.y_axis = pixel.y_axis * proportion;
	spaced_pixel.z_axis = pixel.z_axis * proportion;
	spaced_pixel.rgba_channel = pixel.rgba_channel;
	return (spaced_pixel);
}

//adicionar zoom além do offset
//usar t_camera como parametro
t_line_info	get_x_and_y(t_pixel start, t_pixel end, t_fdf fdf)
{
	t_line_info	line_info;

	line_info.x1 = start.x_axis + fdf.camera.x_offset;
	line_info.y1 = start.y_axis + fdf.camera.y_offset;
	line_info.x2 = end.x_axis + fdf.camera.x_offset;
	line_info.y2 = end.y_axis + fdf.camera.y_offset;
	return (line_info);
}
