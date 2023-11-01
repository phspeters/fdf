/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:49:23 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/01 15:49:07 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_valid_pixel(mlx_image_t *img, int x, int y,	uint32_t color)
{
	if ((x > 0 && x < WIDTH) && (y > 0 && y < HEIGHT))
		mlx_put_pixel(img, x, y, color);
}

t_line_info	set_line_info(t_pixel start, t_pixel end, t_master master)
{
	t_line_info	line_info;

	line_info.x1 = (start.x_axis * master.zoom) + master.x_offset;
	line_info.y1 = (start.y_axis * master.zoom) + master.y_offset;
	line_info.x2 = (end.x_axis * master.zoom) + master.x_offset;
	line_info.y2 = (end.y_axis * master.zoom) + master.y_offset;
	line_info.dx = line_info.x2 - line_info.x1;
	line_info.dy = line_info.y2 - line_info.y1;
	line_info.abs_dx = abs(line_info.dx);
	line_info.abs_dy = abs(line_info.dy);
	return (line_info);
}

void	move_coordinate(int *coordinate, int direction)
{
	if (direction < 0)
		*coordinate -= 1;
	else
		*coordinate += 1;
}

void	draw_line_closer_to_y_axis(t_line_info line_info, t_master *master,
		uint32_t color)
{
	int				decision;
	unsigned int	i;

	put_valid_pixel(master->image, line_info.x1, line_info.y1, color);
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
		put_valid_pixel(master->image, line_info.x1, line_info.y1, color);
		i++;
	}
}

void	draw_line_closer_to_x_axis(t_line_info line_info, t_master *master,
		uint32_t color)
{
	int				decision;
	unsigned int	i;

	put_valid_pixel(master->image, line_info.x1, line_info.y1, color);
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
		put_valid_pixel(master->image, line_info.x1, line_info.y1, color);
		i++;
	}
}

void	draw_line_bresenham(t_pixel start, t_pixel end, t_master *master)
{
	t_line_info	line_info;
	t_pixel		iso_start;
	t_pixel		iso_end;

	iso_start = to_isometric_projection(start);
	iso_end = to_isometric_projection(end);
	line_info = set_line_info(iso_start, iso_end, *master);
	if (line_info.abs_dx > line_info.abs_dy)
		draw_line_closer_to_x_axis(line_info, master, 0xFFFFFFFF);
	else
		draw_line_closer_to_y_axis(line_info, master, 0xFFFFFFFF);
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
