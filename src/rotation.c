/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:56:37 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/17 14:31:55 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_around_x_axis(t_pixel *pixel, float angle)
{
	float	y;
	float	z;

	angle = angle * M_PI / 180;
	y = pixel->y_axis;
	z = pixel->z_axis;
	pixel->y_axis = (y * cos(angle)) - (z * sin(angle));
	pixel->z_axis = (y * sin(angle)) + (z * cos(angle));
}

void	rotate_around_y_axis(t_pixel *pixel, float angle)
{
	float	x;
	float	z;

	angle = angle * M_PI / 180;
	x = pixel->x_axis;
	z = pixel->z_axis;
	pixel->x_axis = (x * cos(angle)) + (z * sin(angle));
	pixel->z_axis = (-x * sin(angle)) + (z * cos(angle));
}

void	rotate_around_z_axis(t_pixel *pixel, float angle)
{
	float	x;
	float	y;

	angle = angle * M_PI / 180;
	x = pixel->x_axis;
	y = pixel->y_axis;
	pixel->x_axis = (x * cos(angle)) - (y * sin(angle));
	pixel->y_axis = (x * sin(angle)) + (y * cos(angle));
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

void	to_isometric(t_pixel *pixel)
{
	rotate_around_z_axis(pixel, -45);
	rotate_around_x_axis(pixel, 54);
}
