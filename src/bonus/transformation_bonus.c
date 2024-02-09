/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:28:11 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/09 11:06:50 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
 * @brief Applies an oblique transformation to the pixel passed as the argument.
 * It essentially rotates the pixel around the z axis by 45 degrees and then
 * translates it by the z axis.
 * 
 * @param pixel Pointer to the pixel to be transformed. 
 */
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
