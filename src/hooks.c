/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:07:52 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/01 15:06:24 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	generic_key_hook(void *param)
{
	t_master	*master;

	master = param;
	if (mlx_is_key_down(master->window, MLX_KEY_ESCAPE))
		mlx_close_window(master->window);
	if (mlx_is_key_down(master->window, MLX_KEY_UP))
		master->y_offset += 10;
	if (mlx_is_key_down(master->window, MLX_KEY_DOWN))
		master->y_offset -= 10;
	if (mlx_is_key_down(master->window, MLX_KEY_LEFT))
		master->x_offset -= 10;
	if (mlx_is_key_down(master->window, MLX_KEY_RIGHT))
		master->x_offset += 10;
}
