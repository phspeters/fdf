/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_draw_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:49:23 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/20 20:56:16 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	draw_line(t_pixel start, t_pixel end, t_fdf *fdf)
{
	t_line_info	line_info;

	line_info = set_line_info(start, end, fdf->camera, fdf->current_map);
	if (line_info.abs_dx > line_info.abs_dy)
		draw_line_closer_to_x_axis(line_info, fdf->image);
	else
		draw_line_closer_to_y_axis(line_info, fdf->image);
}

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

t_line_info	get_line_coordinates(t_pixel start, t_pixel end, t_camera camera, t_map map)
{
	t_line_info	line_info;

	rotate_pixel(&start, camera);
	rotate_pixel(&end, camera);
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

void	draw_line_closer_to_x_axis(t_line_info line_info, mlx_image_t *image)
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
			line_info.start_color);
		i++;
	}
}

void	draw_line_closer_to_y_axis(t_line_info line_info, mlx_image_t *image)
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
			line_info.start_color);
		i++;
	}
}
