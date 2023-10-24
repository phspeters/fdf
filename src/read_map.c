/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:14:12 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/24 16:00:16 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**get_line_of_coordinates(int fd)
{
	char	*line;
	char	**coordinates;

	line = ft_get_next_line(fd);
	coordinates = ft_split(line, ' ');
	free(line);
	return (coordinates);
}

uint32_t	get_color(char *coordinate)
{
	char	*comma_address;

	comma_address = ft_strchr(coordinate, ',');
	if (comma_address)
		return (0);
		//return (ft_atol_base(++comma_address));
	return (-1);
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
	h = 0;
	while (h < height)
	{
		pixels[h] = malloc(width * sizeof(t_pixel));
		ft_free_ptr_array((void **)splitted_line, width);
		splitted_line = get_line_of_coordinates(fd);
		w = 0;
		while (w < width)
		{
			pixels[h][w].x_axis = w;
			pixels[h][w].y_axis = h;
			pixels[h][w].z_axis = ft_atoi(splitted_line[w]);
			pixels[h][w].rgba_channel = get_color(splitted_line[w]);
			w++;
		}
		h++;
	}
	ft_free_ptr_array((void **)splitted_line, height);
	close(fd);
	return (pixels);
}
