/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peters <peters@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:14:12 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/24 21:01:27 by peters           ###   ########.fr       */
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
	return (-1);
}
		//return (ft_atol_base(++comma_address));

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
	h = 0;
	while (h < height)
	{
		pixels[h] = malloc(width * sizeof(t_pixel));
		ft_free_str_array(splitted_line);
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
	ft_free_str_array(splitted_line);
	close(fd);
	return (pixels);
}
