/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:41:55 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/09 16:35:04 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/**
 * @brief Sets the hook to translate the map when the arrow keys are pressed.
 * 
 * @param param Pointer to the main struct of the program.
 */
void	translate_loop_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->window, MLX_KEY_UP))
		fdf->camera.y_offset -= 10;
	if (mlx_is_key_down(fdf->window, MLX_KEY_DOWN))
		fdf->camera.y_offset += 10;
	if (mlx_is_key_down(fdf->window, MLX_KEY_LEFT))
		fdf->camera.x_offset -= 10;
	if (mlx_is_key_down(fdf->window, MLX_KEY_RIGHT))
		fdf->camera.x_offset += 10;
}

/**
 * @brief Sets the hook to rotate the map base on keyboard input.
 * Because it is a generic hook, it doesn't support holding the key down.
 * 
 * @param keydata Struct with the key data.
 * @param param Pointer to the main struct of the program.
 */
void	rotate_loop_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->window, MLX_KEY_S))
		fdf->camera.x_angle -= 1;
	if (mlx_is_key_down(fdf->window, MLX_KEY_W))
		fdf->camera.x_angle += 1;
	if (mlx_is_key_down(fdf->window, MLX_KEY_A))
		fdf->camera.y_angle -= 1;
	if (mlx_is_key_down(fdf->window, MLX_KEY_D))
		fdf->camera.y_angle += 1;
	if (mlx_is_key_down(fdf->window, MLX_KEY_Q))
		fdf->camera.z_angle -= 1;
	if (mlx_is_key_down(fdf->window, MLX_KEY_E))
		fdf->camera.z_angle += 1;
}

/**
 * @brief Sets the key hook to rotate the map base on keyboard input.
 * Because it is a specific hook, it supports holding the key to give continuous
 * input. It's responsible for rotating the map faster when pressing the shift
 * key in conjunction with the rotation key.
 * 
 * @param keydata Struct with the key data.
 * @param param Pointer to the main struct of the program.
 */
void	rotate_key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keydata.key == MLX_KEY_S && keydata.modifier == MLX_SHIFT && \
	keydata.action == MLX_REPEAT)
		fdf->camera.x_angle -= 2;
	if (keydata.key == MLX_KEY_W && keydata.modifier == MLX_SHIFT && \
	keydata.action == MLX_REPEAT)
		fdf->camera.x_angle += 2;
	if (keydata.key == MLX_KEY_A && keydata.modifier == MLX_SHIFT && \
	keydata.action == MLX_REPEAT)
		fdf->camera.y_angle -= 2;
	if (keydata.key == MLX_KEY_D && keydata.modifier == MLX_SHIFT && \
	keydata.action == MLX_REPEAT)
		fdf->camera.y_angle += 2;
	if (keydata.key == MLX_KEY_Q && keydata.modifier == MLX_SHIFT && \
	keydata.action == MLX_REPEAT)
		fdf->camera.z_angle -= 2;
	if (keydata.key == MLX_KEY_E && keydata.modifier == MLX_SHIFT && \
	keydata.action == MLX_REPEAT)
		fdf->camera.z_angle += 2;
}

/**
 * @brief Sets the hook to zoom the map base on keyboard input.
 * 
 * @param param Pointer to the main struct of the program.
 */
void	zoom_loop_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->window, MLX_KEY_EQUAL))
		fdf->camera.zoom *= 1.05;
	if (mlx_is_key_down(fdf->window, MLX_KEY_MINUS))
		fdf->camera.zoom *= 0.95;
}

/**
 * @brief Sets the hook to zoom the map base on mouse input.
 * 
 * @param xdelta The amount of horizontal scroll.
 * @param ydelta The amount of vertical scroll.
 * @param param Pointer to the main struct of the program.
 */
void	zoom_scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (ydelta > 0)
		fdf->camera.zoom *= 1.05;
	if (ydelta < 0)
		fdf->camera.zoom *= 0.95;
	if (xdelta)
		fdf->camera.zoom *= 1;
}
