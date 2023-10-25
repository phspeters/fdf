/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peters <peters@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:14:12 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/24 21:26:13 by peters           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	**get_line_of_coordinates(int fd)
{
	char	*line;
	char	**coordinates;

	line = ft_get_next_line(fd);
	coordinates = ft_split(line, ' ');
	free(line);
	return (coordinates);
}

static uint32_t	get_color(char *coordinate)
{
	char	*comma_address;

	comma_address = ft_strchr(coordinate, ',');
	if (comma_address)
		return (0);
	return (-1);
}
// return (ft_atol_base(++comma_address));

void	populate_pixel_matrix(t_pixel *pixel, char *str, int h, int w)
{
	pixel->x_axis = w;
	pixel->y_axis = h;
	pixel->z_axis = ft_atoi(str);
	pixel->rgba_channel = get_color(str);
}

t_pixel	**read_map(char *filename, int width, int height)
{
	t_pixel	**pixels;
	int		h;
	int		w;
	int		fd;
	char	**splitted_line;

	fd = open(filename, O_RDONLY);
	pixels = malloc(height * sizeof(t_pixel *));
	splitted_line = NULL;
	h = -1;
	while (++h < height)
	{
		pixels[h] = malloc(width * sizeof(t_pixel));
		ft_free_str_array(splitted_line);
		splitted_line = get_line_of_coordinates(fd);
		w = -1;
		while (++w < width)
			populate_pixel_matrix(&pixels[h][w], splitted_line[w], h, w);
	}
	ft_free_str_array(splitted_line);
	close(fd);
	return (pixels);
}
