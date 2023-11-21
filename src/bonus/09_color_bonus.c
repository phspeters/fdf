/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_color_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:58:22 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/21 17:50:33 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

uint32_t	interpolate_color(uint32_t color1, uint32_t color2,
	float percentage)
{
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	uint32_t	alpha;

	red = (uint32_t)((1 - percentage) * ((color1 >> 24) & 0xFF) + percentage
			* ((color2 >> 24) & 0xFF));
	green = (uint32_t)((1 - percentage) * ((color1 >> 16) & 0xFF) + percentage
			* ((color2 >> 16) & 0xFF));
	blue = (uint32_t)((1 - percentage) * ((color1 >> 8) & 0xFF) + percentage
			* ((color2 >> 8) & 0xFF));
	alpha = (uint32_t)((1 - percentage) * (color1 & 0xFF) + percentage
			* (color2 & 0xFF));
	return ((red << 24) | (green << 16) | blue << 8 | alpha);
}
