/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_render_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:35:52 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/22 14:30:04 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	render_background(t_fdf *fdf)
{
	unsigned int	h;
	unsigned int	w;

	h = -1;
	while (++h < HEIGHT)
	{
		w = -1;
		while (++w < WIDTH)
		{
			put_valid_pixel(fdf->image, w, h, fdf->map_info.background_color);
		}
	}
}

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

void	render_controls_menu(t_fdf *fdf)
{
	int	h;
	int	w;

	h = -1;
	while (++h < MENU_HEIGHT)
	{
		w = -1;
		while (++w < MENU_WIDTH)
		{
			put_valid_pixel(fdf->image, w, h, 0x77777777);
		}
	}
}

void	print_controls_on_the_screen(t_fdf *fdf)
{
	mlx_put_string(fdf->window, "CONTROLS:", 10, 10);
	mlx_put_string(fdf->window, "W, S -> X rotation", 10, 30);
	mlx_put_string(fdf->window, "A, D -> Y rotation", 10, 50);
	mlx_put_string(fdf->window, "Q, E -> Z rotation", 10, 70);
	mlx_put_string(fdf->window, "SHIFT + rotation -> Speed up", 10, 90);
	mlx_put_string(fdf->window, "Up, Down, Left, Right -> Move", 10, 110);
	mlx_put_string(fdf->window, "-, = -> Zoom in or out", 10, 130);
	mlx_put_string(fdf->window, "Mouse Scroll -> Zoom in or out", 10, 150);
	mlx_put_string(fdf->window, "R -> Randomize background color", 10, 170);
	mlx_put_string(fdf->window, "F -> Disable background", 10, 190);
	mlx_put_string(fdf->window, "1, 2, 3 -> Change projection", 10, 210);
	mlx_put_string(fdf->window, "Space -> Reset position", 10, 230);
}
