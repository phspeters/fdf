/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:29:45 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/21 12:39:31 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	put_valid_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if ((x > 0 && x < WIDTH) && (y > 0 && y < HEIGHT))
		mlx_put_pixel(img, x, y, color);
}

void	move_coordinate(int *coordinate, int direction)
{
	if (direction < 0)
		*coordinate -= 1;
	else
		*coordinate += 1;
}

void	refresh_corner_pixels(t_pixel pixel, t_map *map)
{
	if (pixel.x_axis > map->x_max)
		map->x_max = pixel.x_axis;
	if (pixel.x_axis < map->x_min)
		map->x_min = pixel.x_axis;
	if (pixel.y_axis > map->y_max)
		map->y_max = pixel.y_axis;
	if (pixel.y_axis < map->y_min)
		map->y_min = pixel.y_axis;
}

void	refresh_min_and_max_z(int z_axis, t_map_info *map_info)
{
	if (z_axis > map_info->max_z)
		map_info->max_z = z_axis;
	if (z_axis < map_info->min_z)
		map_info->min_z = z_axis;
}

void	free_maps(t_fdf *fdf)
{
	ft_free_ptr_array((void **)fdf->parallel.pixels, fdf->map_info.height);
	ft_free_ptr_array((void **)fdf->isometric.pixels, fdf->map_info.height);
	ft_free_ptr_array((void **)fdf->oblique.pixels, fdf->map_info.height);
}
