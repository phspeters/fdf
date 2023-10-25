/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peters <peters@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:51:03 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/24 21:28:12 by peters           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"

// Bytes Per Pixel. Since each pixel is represented as an integer, it will be
// four bytes for four channels.

// 'Encodes' four individual bytes into an int.
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// Get the red channel.
// Move 3 bytes to the right and mask out the first byte.
int	get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
// Move 2 bytes to the right and mask out the first byte.
int	get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
// Move 1 byte to the right and mask out the first byte.
int	get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
// Move 0 bytes to the right and mask out the first byte.
int	get_a(int rgba)
{
	return (rgba & 0xFF);
}
