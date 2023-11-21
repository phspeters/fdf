/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_transformation_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:28:11 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/21 17:50:25 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	to_isometric(t_pixel *pixel)
{
	rotate_around_z_axis(pixel, -45);
	rotate_around_x_axis(pixel, 54);
}

void	to_oblique(t_pixel *pixel)
{
	float	x;
	float	y;
	float	angle;

	angle = 45 * M_PI / 180;
	x = pixel->x_axis;
	y = pixel->y_axis;
	pixel->x_axis = x + (pixel->z_axis * sin(angle));
	pixel->y_axis = y - (pixel->z_axis * sin(angle));
}

void	to_parallel(t_pixel *pixel)
{
	pixel->x_axis = pixel->x_axis;
}
