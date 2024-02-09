/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:28:11 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/07 21:28:35 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Applies an isometric transformation to the pixel passed as the
 * argument. It essentially rotates the pixel around the z axis by -45 degrees
 * and then around the x axis by 54 degrees.
 * 
 * @param pixel Pointer to the pixel to be transformed. 
 */
void	to_isometric(t_pixel *pixel)
{
	rotate_around_z_axis(pixel, -45);
	rotate_around_x_axis(pixel, 54);
}

/**
 * @brief Rotates the pixel around the z axis by the angle passed as the second
 * argument. It uses the rotation matrix to perform the rotation.
 * 
 * @param pixel Pointer to the pixel to be transformed.
 * @param angle Angle in degree	s to rotate the pixel around the z axis.
 */
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

/**
 * @brief Rotates the pixel around the x axis by the angle passed as the second
 * argument. It uses the rotation matrix to perform the rotation.
 * 
 * @param pixel Pointer to the pixel to be transformed.
 * @param angle Angle in degrees to rotate the pixel around the x axis.
 */
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
