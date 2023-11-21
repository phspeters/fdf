/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:53:03 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/20 20:22:08 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	handle_mlx_error(t_fdf *fdf)
{
	int	exit_code;

	free_maps(fdf);
	exit_code = ft_fprintf(STDERR_FILENO, "%s", mlx_strerror(mlx_errno));
	exit(exit_code);
}

//void	handle_error(t_fdf *fdf)
//{
//	free_maps(fdf);
//	exit();
//}
