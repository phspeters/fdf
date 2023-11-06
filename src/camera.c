/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:02:20 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/06 18:13:25 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_x_offset(t_master master)
{
	t_pixel	left_corner;
	t_pixel	right_corner;
	int		min_x;
	int		max_x;
	int		average_x;

	left_corner = master.pixels[master.map_height - 1][0];
	right_corner = master.pixels[0][master.map_width - 1];
	left_corner = apply_zoom(left_corner, master.zoom);
	right_corner = apply_zoom(right_corner, master.zoom);
	left_corner = to_isometric(left_corner);
	right_corner = to_isometric(right_corner);
	min_x = left_corner.x_axis;
	max_x = right_corner.x_axis;
	average_x = (max_x - min_x) / 2;
	return (max_x - average_x);
}

int	get_y_offset(t_master master)
{
	t_pixel	upper_corner;
	t_pixel	bottom_corner;
	int		min_y;
	int		max_y;
	int		average_y;

	upper_corner = master.pixels[0][0];
	bottom_corner = master.pixels[master.map_height - 1][master.map_width - 1];
	upper_corner = apply_zoom(upper_corner, master.zoom);
	bottom_corner = apply_zoom(bottom_corner, master.zoom);
	upper_corner = to_isometric(upper_corner);
	bottom_corner = to_isometric(bottom_corner);
	min_y = upper_corner.y_axis;
	max_y = bottom_corner.y_axis;
	average_y = (max_y - min_y) / 2;
	return (max_y - average_y);
}

void	init_camera(t_master *master)
{
	master->zoom = fmin(round((WIDTH / master->map_width)), round((HEIGHT
					/ master->map_height)));
	master->x_offset = WIDTH / 2 - get_x_offset(*master);
	master->y_offset = HEIGHT / 2 - get_y_offset(*master);
}
