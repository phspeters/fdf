/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@42sp.com.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:55:06 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/01 21:10:08 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel	to_isometric_projection(t_pixel pixel)
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
