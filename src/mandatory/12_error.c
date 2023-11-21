/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:53:03 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/21 17:11:31 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_mlx_error(t_fdf *fdf)
{
	free_maps(fdf);
	ft_fprintf(STDERR_FILENO, "%s\n", mlx_strerror(mlx_errno));
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
		ft_fprintf(STDERR_FILENO, "%s\n", message);
		exit(EXIT_FAILURE);
	}
}
