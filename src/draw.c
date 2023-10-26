/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:49:23 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/26 16:08:57 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line_info	set_bresenham_info(t_pixel pixel, char flag, t_master master)
{
	t_line_info	line_info;

	line_info.x1 = pixel.x_axis * master.zoom;
	line_info.y1 = pixel.y_axis * master.zoom;
	if (flag == 'w')
	{
		line_info.x2 = (pixel.x_axis + 1) * master.zoom;
		line_info.y2 = pixel.y_axis * master.zoom;
	}
	else if (flag == 'h')
	{
		line_info.x2 = pixel.x_axis * master.zoom;
		line_info.y2 = (pixel.y_axis + 1) * master.zoom;
	}
	line_info.dx = line_info.x2 - line_info.x1;
	line_info.dy = line_info.y2 - line_info.y1;
	line_info.abs_dx = abs(line_info.dx);
	line_info.abs_dy = abs(line_info.dy);
	return (line_info);
}

void	draw_line_closer_to_y_axis(t_line_info line_info, t_master *master,
		t_pixel pixel)
{
	int				decision;
	unsigned int	i;

	decision = 2 * line_info.abs_dx - line_info.abs_dy;
	i = 0;
	while (i < line_info.abs_dy)
	{
		if (line_info.dy < 0)
			line_info.y1--;
		else
			line_info.y1++;
		if (decision < 0)
			decision = decision + 2 * line_info.abs_dx;
		else
		{
			if (line_info.dx < 0)
				line_info.x1--;
			else
				line_info.x1++;
			decision = decision + (2 * line_info.abs_dx - 2 * line_info.abs_dy);
		}
		mlx_put_pixel(master->image, line_info.x1, line_info.y1,
			pixel.rgba_channel);
		i++;
	}
}

void	draw_line_closer_to_x_axis(t_line_info line_info, t_master *master,
		t_pixel pixel)
{
	int				decision;
	unsigned int	i;

	decision = 2 * line_info.abs_dy - line_info.abs_dx;
	i = 0;
	while (i < line_info.abs_dx)
	{
		if (line_info.dx < 0)
			line_info.x1--;
		else
			line_info.x1++;
		if (decision < 0)
			decision = decision + 2 * line_info.abs_dy;
		else
		{
			if (line_info.dy < 0)
				line_info.y1--;
			else
				line_info.y1++;
			decision = decision + (2 * line_info.abs_dy - 2 * line_info.abs_dx);
		}
		mlx_put_pixel(master->image, line_info.x1, line_info.y1,
			pixel.rgba_channel);
		i++;
	}
}

void	draw_line_bresenham(t_pixel pixel, char flag, t_master *master)
{
	t_line_info		line_info;

	line_info = set_bresenham_info(pixel, flag, *master);
	mlx_put_pixel(master->image, line_info.x1, line_info.y1,
		pixel.rgba_channel);
	if (line_info.abs_dx > line_info.abs_dy)
		draw_line_closer_to_x_axis(line_info, master, pixel);
	else
		draw_line_closer_to_y_axis(line_info, master, pixel);
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
			if (w + 1 < width)
				draw_line_bresenham(master->pixels[h][w], 'w', master);
			if (h + 1 < height)
				draw_line_bresenham(master->pixels[h][w], 'h', master);
			w++;
		}
		h++;
	}
}
