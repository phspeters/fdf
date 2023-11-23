/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:53:03 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/23 12:17:42 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	handle_mlx_error(t_fdf *fdf)
{
	free_maps(fdf);
	ft_fprintf(STDERR_FILENO, "%s.\n", mlx_strerror(mlx_errno));
	exit(mlx_errno);
}

void	handle_error(char *message)
{
	if (errno)
	{
		perror(message);
		exit(errno);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "%s.\n", message);
		exit(EXIT_FAILURE);
	}
}
