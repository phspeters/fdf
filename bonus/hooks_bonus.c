/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:07:52 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/19 21:24:24 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	close_key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(fdf->window);
}

void	rotate_key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keydata.key == MLX_KEY_U && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera.x_angle -= 1;
	if (keydata.key == MLX_KEY_J && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera.x_angle += 1;
	if (keydata.key == MLX_KEY_I && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera.y_angle -= 1;
	if (keydata.key == MLX_KEY_K && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera.y_angle += 1;
	if (keydata.key == MLX_KEY_O && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera.z_angle -= 1;
	if (keydata.key == MLX_KEY_L && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera.z_angle += 1;
}

void	translate_key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if ((keydata.key == MLX_KEY_UP || (keydata.key == MLX_KEY_W)) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera.y_offset -= 10;
	if ((keydata.key == MLX_KEY_DOWN || (keydata.key == MLX_KEY_S)) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera.y_offset += 10;
	if ((keydata.key == MLX_KEY_LEFT || (keydata.key == MLX_KEY_A)) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera.x_offset -= 10;
	if ((keydata.key == MLX_KEY_RIGHT || (keydata.key == MLX_KEY_D)) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera.x_offset += 10;
}

void	zoom_key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera.zoom *= 1.05;
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera.zoom *= 0.95;
}

void	select_projection_key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keydata.key == MLX_KEY_1 && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->current_map = &fdf->isometric;
	if (keydata.key == MLX_KEY_2 && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->current_map = &fdf->oblique;
	if (keydata.key == MLX_KEY_3 && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->current_map = &fdf->parallel;
}

void	z_scale_key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keydata.key == MLX_KEY_Z && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		fdf->camera.z_scale *= 1.05;
		ft_free_ptr_array((void **)fdf->isometric.pixels, fdf->map_info.height);
		ft_free_ptr_array((void **)fdf->oblique.pixels, fdf->map_info.height);
		init_map(&fdf->isometric, *fdf);
		transform_map(&fdf->isometric, fdf, to_isometric);
		init_map(&fdf->oblique, *fdf);
		transform_map(&fdf->oblique, fdf, to_oblique);
	}
	if (keydata.key == MLX_KEY_C && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		fdf->camera.z_scale *= 0.95;
		ft_free_ptr_array((void **)fdf->isometric.pixels, fdf->map_info.height);
		ft_free_ptr_array((void **)fdf->oblique.pixels, fdf->map_info.height);
		init_map(&fdf->isometric, *fdf);
		transform_map(&fdf->isometric, fdf, to_isometric);
		init_map(&fdf->oblique, *fdf);
		transform_map(&fdf->oblique, fdf, to_oblique);
	}
}

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
