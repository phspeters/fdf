/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@42sp.com.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:07:52 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/27 16:23:46 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	generic_key_hook(void *param)
{
	t_master	*master;

	master = param;
	if (mlx_is_key_down(master->window, MLX_KEY_ESCAPE))
		mlx_close_window(master->window);
}
	//if (mlx_is_key_down(master->window, MLX_KEY_UP))
	//	master->image->instances[0].y -= 5;
	//if (mlx_is_key_down(master->window, MLX_KEY_DOWN))
	//	master->image->instances[0].y += 5;
	//if (mlx_is_key_down(master->window, MLX_KEY_LEFT))
	//	master->image->instances[0].x -= 5;
	//if (mlx_is_key_down(master->window, MLX_KEY_RIGHT))
	//	master->image->instances[0].x += 5;