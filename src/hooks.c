/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:07:52 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/14 22:35:51 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	generic_key_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->window, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->window);
	//bonus
	if (mlx_is_key_down(fdf->window, MLX_KEY_W))
		fdf->camera.y_offset -= 10;
	if (mlx_is_key_down(fdf->window, MLX_KEY_S))
		fdf->camera.y_offset += 10;
	if (mlx_is_key_down(fdf->window, MLX_KEY_A))
		fdf->camera.x_offset -= 10;
	if (mlx_is_key_down(fdf->window, MLX_KEY_D))
		fdf->camera.x_offset += 10;
	if (mlx_is_key_down(fdf->window, MLX_KEY_Q))
		fdf->camera.zoom *= 0.9;
	if (mlx_is_key_down(fdf->window, MLX_KEY_E))
		fdf->camera.zoom *= 1.1;
	mlx_delete_image(fdf->window, fdf->image);
	fdf->image = mlx_new_image(fdf->window, WIDTH, HEIGHT);
	mlx_image_to_window(fdf->window, fdf->image, 0, 0);
	draw_map(fdf, fdf->map_info.height, fdf->map_info.width);
}
