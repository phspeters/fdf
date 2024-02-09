/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:58:22 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/09 11:15:07 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Function that performs a color interpolation between two given colors
 * using a percentage factor representing the amount of the second color to be
 * used in the interpolation. It uses bitwise operations and returns the
 * interpolated color in the 0xRRGGBBAA format. That is, a unsigned 32 bits
 * integer where the most significant byte is the red channel, the second byte
 * is the green channel, the third byte is the blue channel and the least
 * significant byte is the alpha channel.
 * 
 * @param color1 First color to be interpolated.
 * @param color2 Second color to be interpolated.
 * @param percentage Percentage of the second color to be used in the
 * interpolation.
 * @return Interpolated color in the 0xRRGGBBAA format.
 */
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
