/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:41:55 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/21 17:13:39 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	close_loop_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->window, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->window);
}
