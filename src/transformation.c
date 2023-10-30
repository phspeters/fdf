/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:55:06 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/30 17:50:42 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	to_isometric_projection(t_pixel *pixel)
{
	int		iso_x;
	int		iso_y;
	float	angle;

	angle = 30 * M_PI / 180;
	iso_x = round((pixel->x_axis - pixel->y_axis) * cos(0.53));
	iso_y = round((pixel->x_axis + pixel->y_axis) * sin(0.53) - pixel->z_axis);
	pixel->x_axis = iso_x;
	pixel->y_axis = iso_y;
}
