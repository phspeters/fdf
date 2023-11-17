/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:29:45 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/16 21:35:47 by pehenri2         ###   ########.fr       */
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

//colocar rotate aqui?
t_line_info	get_x_and_y(t_pixel start, t_pixel end, t_camera camera, t_map map)
{
	t_line_info	line_info;

	if(map.x_max)
	{
		
	}
	line_info.x1 = (start.x_axis * camera.zoom) + camera.x_offset;// - map.x_offset;
	line_info.y1 = (start.y_axis * camera.zoom) + camera.y_offset;// - map.y_offset;
	line_info.x2 = (end.x_axis * camera.zoom) + camera.x_offset;// - map.x_offset;
	line_info.y2 = (end.y_axis * camera.zoom) + camera.y_offset;// - map.y_offset;
	return (line_info);
}
