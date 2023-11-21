/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_rotation_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:56:37 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/20 20:50:18 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	rotate_pixel(t_pixel *pixel, t_camera cam)
{
	rotate_around_x_axis(pixel, cam.x_angle);
	rotate_around_y_axis(pixel, cam.y_angle);
	rotate_around_z_axis(pixel, cam.z_angle);
}

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
