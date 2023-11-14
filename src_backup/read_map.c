/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:14:12 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/08 12:20:49 by pehenri2         ###   ########.fr       */
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
	char		*x_address;
	char		*hexadecimal;
	uint32_t	color;

	x_address = ft_strchr(coordinate, ',');
	if (x_address)
	{
		hexadecimal = ft_strtolower(x_address + 3);
		color = (ft_atoi_base(hexadecimal, "0123456789abcdef") << 8) | 0xff;
		return (color);
	}
	return (0xffffffff);
}

static void	populate_pixel_matrix(t_pixel *pixel, char *str, int h, int w)
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
	if (fd < 0)
		return (NULL);
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
