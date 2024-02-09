/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:35:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/07 21:33:47 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Iterates trough the pixel matrix of the map passed as the first
 * argument and draws lines between the current pixel and the one below it and
 * the  * current pixel and the one to the right of it. It uses the draw_line
 * function to draw the lines.
 * 
 * @param map Pointer to the map to be rendered.
 * @param map_info Information about the map.
 * @param fdf Pointer to the main struct of the program.
 */
void	render_image(t_map *map, t_map_info map_info, t_fdf *fdf)
{
	unsigned int	h;
	unsigned int	w;

	h = -1;
	while (++h < map_info.height)
	{
		w = -1;
		while (++w < map_info.width)
		{
			if (w < map_info.width - 1)
				draw_line(map->pixels[h][w], map->pixels[h][w + 1],
					fdf);
			if (h < map_info.height - 1)
				draw_line(map->pixels[h][w], map->pixels[h + 1][w],
					fdf);
		}
	}
}
