/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:49:23 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/25 18:52:59 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_bresenham(int x, int y, int x2, int y2, t_master *master)
{
	int				dx;
	int				dy;
	unsigned int	abs_dx;
	unsigned int	abs_dy;
	int				decision;
	unsigned int	i;

	dx = x2 - x;
	dy = y2 - y;
	abs_dx = abs(dx);
	abs_dy = abs(dy);
	mlx_put_pixel(master->image, x, y, 0xFFFF00FF);
	if (abs_dx > abs_dy)
	{
		decision = 2 * abs_dy - abs_dx;
		i = 0;
		while (i < abs_dx)
		{
			if (dx < 0)
				x--;
			else
				x++;
			if (decision < 0)
			{
				decision = decision + 2 * abs_dy;
			}
			else
			{
				if (dy < 0)
					y--;
				else
					y++;
				decision = decision + (2 * abs_dy - 2 * abs_dx);
			}
			mlx_put_pixel(master->image, x, y,0xFFFF00FF);
			i++;
		}
	}
	else
	{ // case when slope is greater than or equals to 1
		decision = 2 * abs_dx - abs_dy;
		i = 0;
		while (i < abs_dy)
		{
			if (dy < 0)
				y--;
			else
				y++;
			if (decision < 0)
				decision = decision + 2 * abs_dx;
			else
			{
				if (dx < 0)
					x--;
				else
					x++;
				decision = decision + (2 * abs_dx) - (2 * abs_dy);
			}
			mlx_put_pixel(master->image, x, y, 0xFFFF00FF);
			i++;
		}
	}
}

void	draw_map(t_master *master, int height, int width)
{
	int	h;
	int	w;

	h = 0;
	while (h < height)
	{
		w = 0;
		while (w < width)
		{
			if (w + 1 < width)
				draw_line_bresenham(w, h, w + 1, h, master);
			if (h + 1 < height)
				draw_line_bresenham(w, h, w, h + 1, master);
			w++;
		}
		h++;
	}
}
