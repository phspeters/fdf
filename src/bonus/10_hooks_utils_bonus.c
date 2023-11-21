/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_hooks_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:07:52 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/20 20:49:37 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	select_projection_loop_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->window, MLX_KEY_1))
		fdf->current_map = &fdf->isometric;
	if (mlx_is_key_down(fdf->window, MLX_KEY_2))
		fdf->current_map = &fdf->oblique;
	if (mlx_is_key_down(fdf->window, MLX_KEY_3))
		fdf->current_map = &fdf->parallel;
}

void	reset_position_loop_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->window, MLX_KEY_SPACE))
	{
		fdf->camera.x_angle = 0;
		fdf->camera.y_angle = 0;
		fdf->camera.z_angle = 0;
		fdf->camera.x_offset = WIDTH / 2;
		fdf->camera.y_offset = HEIGHT / 2;
		set_initial_zoom(fdf->current_map, &fdf->camera.zoom);
	}
}

void	close_loop_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->window, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->window);
}
