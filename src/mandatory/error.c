/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:53:03 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/07 21:39:26 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Used when some MLX42 library function returns an error. It's
 * responsible for freeing the memory allocated for the maps, printing the error
 * message and exiting the program with the corresponding mlx_errno.
 * 
 * @param fdf 
 */
void	handle_mlx_error(t_fdf *fdf)
{
	free_maps(fdf);
	ft_fprintf(STDERR_FILENO, "%s.\n", mlx_strerror(mlx_errno));
	exit(mlx_errno);
}

/**
 * @brief Used to handle errors in the program. It's responsible for printing
 * the error message and exiting the program with the corresponding errno.
 * 
 * @param message String containing the error message.
 */
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
