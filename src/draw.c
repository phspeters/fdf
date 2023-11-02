/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:49:23 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/02 15:31:47 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line_info	set_line_info(t_pixel start, t_pixel end, t_master master)
{
	t_line_info	line_info;
	t_pixel		iso_start;
	t_pixel		iso_end;

	start = apply_zoom(start, master.zoom);
	end = apply_zoom(end, master.zoom);
	iso_start = to_isometric_projection(start);
	iso_end = to_isometric_projection(end);
	line_info.x1 = iso_start.x_axis + master.x_offset;
	line_info.y1 = iso_start.y_axis + master.y_offset;
	line_info.x2 = iso_end.x_axis + master.x_offset;
	line_info.y2 = iso_end.y_axis + master.y_offset;
	line_info.dx = line_info.x2 - line_info.x1;
	line_info.dy = line_info.y2 - line_info.y1;
	line_info.abs_dx = abs(line_info.dx);
	line_info.abs_dy = abs(line_info.dy);
	line_info.start_color = 0xFFFFFFFF;
	//line_info.start_color = start.rgba_channel;
	//line_info.end_color = end.rgba_channel;
	return (line_info);
}

void	draw_line_closer_to_y_axis(t_line_info line_info, t_master *master)
{
	int				decision;
	unsigned int	i;

	put_valid_pixel(master->image, line_info.x1, line_info.y1,
		line_info.start_color);
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
		put_valid_pixel(master->image, line_info.x1, line_info.y1,
			line_info.start_color);
		i++;
	}
}

void	draw_line_closer_to_x_axis(t_line_info line_info, t_master *master)
{
	int				decision;
	unsigned int	i;

	put_valid_pixel(master->image, line_info.x1, line_info.y1,
		line_info.start_color);
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
		put_valid_pixel(master->image, line_info.x1, line_info.y1,
			line_info.start_color);
		i++;
	}
}

void	draw_line_bresenham(t_pixel start, t_pixel end, t_master *master)
{
	t_line_info	line_info;

	line_info = set_line_info(start, end, *master);
	if (line_info.abs_dx > line_info.abs_dy)
		draw_line_closer_to_x_axis(line_info, master);
	else
		draw_line_closer_to_y_axis(line_info, master);
}

void	draw_map(t_master *master, int height, int width)
{
	int	h;
	int	w;

	h = 0;
	while (h < height)
	{
		w = 0;
		while (w < width)
		{
			if (w < width - 1)
				draw_line_bresenham(master->pixels[h][w], master->pixels[h][w
					+ 1], master);
			if (h < height - 1)
				draw_line_bresenham(master->pixels[h][w], master->pixels[h
					+ 1][w], master);
			w++;
		}
		h++;
	}
}
