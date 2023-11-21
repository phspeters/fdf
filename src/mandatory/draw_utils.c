/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:29:45 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/20 18:10:47 by pehenri2         ###   ########.fr       */
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

void	refresh_corner_pixels(t_pixel pixel, t_map *map)
{
	if (pixel.x_axis > map->x_max)
		map->x_max = pixel.x_axis;
	if (pixel.x_axis < map->x_min)
		map->x_min = pixel.x_axis;
	if (pixel.y_axis > map->y_max)
		map->y_max = pixel.y_axis;
	if (pixel.y_axis < map->y_min)
		map->y_min = pixel.y_axis;
}

t_line_info	get_x_and_y(t_pixel start, t_pixel end, t_camera camera, t_map map)
{
	t_line_info	line_info;

	line_info.x1 = ((start.x_axis - map.x_offset_correction) * camera.zoom)
		+ camera.x_offset;
	line_info.y1 = ((start.y_axis - map.y_offset_correction) * camera.zoom)
		+ camera.y_offset;
	line_info.x2 = ((end.x_axis - map.x_offset_correction) * camera.zoom)
		+ camera.x_offset;
	line_info.y2 = ((end.y_axis - map.y_offset_correction) * camera.zoom)
		+ camera.y_offset;
	return (line_info);
}
