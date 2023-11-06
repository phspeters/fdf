/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:07:52 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/06 16:20:10 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	generic_key_hook(void *param)
{
	t_master	*master;

	master = param;
	if (mlx_is_key_down(master->window, MLX_KEY_ESCAPE))
		mlx_close_window(master->window);
	//bonus
	if (mlx_is_key_down(master->window, MLX_KEY_W))
		master->y_offset -= 10;
	if (mlx_is_key_down(master->window, MLX_KEY_S))
		master->y_offset += 10;
	if (mlx_is_key_down(master->window, MLX_KEY_A))
		master->x_offset -= 10;
	if (mlx_is_key_down(master->window, MLX_KEY_D))
		master->x_offset += 10;
	if (mlx_is_key_down(master->window, MLX_KEY_Q))
		master->zoom -= 1;
	if (mlx_is_key_down(master->window, MLX_KEY_E))
		master->zoom += 1;
	mlx_delete_image(master->window, master->image);
	master->image = mlx_new_image(master->window, WIDTH, HEIGHT);
	mlx_image_to_window(master->window, master->image, 0, 0);
	draw_map(master, master->map_height, master->map_width);
}
