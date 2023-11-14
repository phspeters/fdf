/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:02:20 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/08 14:12:47 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel	get_upper_corner(t_master master)
{
	t_pixel			upper_corner;
	t_pixel			current_pixel;
	unsigned int	h;
	unsigned int	w;

	h = -1;
	upper_corner = master.pixels[0][0];
	while (++h < master.map_height)
	{
		w = -1;
		while (++w < master.map_width)
		{
			current_pixel = apply_distance(master.pixels[h][w],
				master.pixel_distance);
			current_pixel = to_isometric(current_pixel);
			if (current_pixel.y_axis < upper_corner.y_axis)
				upper_corner = master.pixels[h][w];
		}
	}
	return (upper_corner);
}

t_pixel	get_bottom_corner(t_master master)
{
	t_pixel			bottom_corner;
	t_pixel			current_pixel;
	unsigned int	h;
	unsigned int	w;

	h = -1;
	bottom_corner = master.pixels[master.map_height - 1][master.map_width - 1];
	while (++h < master.map_height)
	{
		w = -1;
		while (++w < master.map_width)
		{
			current_pixel = to_isometric(current_pixel);
			current_pixel = apply_distance(master.pixels[h][w],
				master.pixel_distance);
			if (current_pixel.y_axis > bottom_corner.y_axis)
				bottom_corner = master.pixels[h][w];
		}
	}
	return (bottom_corner);
}

int	get_y_offset(t_master master)
{
	t_pixel	upper_corner;
	t_pixel	bottom_corner;
	int		min_y;
	int		max_y;
	int		average_y;

	upper_corner = get_upper_corner(master);
	bottom_corner = get_bottom_corner(master);
	upper_corner = apply_distance(upper_corner, master.pixel_distance);
	bottom_corner = apply_distance(bottom_corner, master.pixel_distance);
	upper_corner = to_isometric(upper_corner);
	bottom_corner = to_isometric(bottom_corner);
	min_y = upper_corner.y_axis;
	max_y = bottom_corner.y_axis;
	average_y = (max_y - min_y) / 2;
	return (max_y - average_y);
}

int	get_x_offset(t_master master)
{
	t_pixel	left_corner;
	t_pixel	right_corner;
	int		min_x;
	int		max_x;
	int		average_x;

	left_corner = master.pixels[master.map_height - 1][0];
	right_corner = master.pixels[0][master.map_width - 1];
	left_corner = apply_distance(left_corner, master.pixel_distance);
	right_corner = apply_distance(right_corner, master.pixel_distance);
	left_corner = to_isometric(left_corner);
	right_corner = to_isometric(right_corner);
	min_x = left_corner.x_axis;
	max_x = right_corner.x_axis;
	average_x = (max_x - min_x) / 2;
	return (max_x - average_x);
}

void	init_camera(t_master *master)
{
	float	width_distance;
	float	height_distance;

	width_distance = (WIDTH / (float)master->map_width);
	height_distance = (HEIGHT / (float)master->map_height);
	master->pixel_distance = fminf(width_distance, height_distance) * 0.8;
	master->x_offset = WIDTH / 2 - get_x_offset(*master);
	master->y_offset = HEIGHT / 2 - get_y_offset(*master);
}
