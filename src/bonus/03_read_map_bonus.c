/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_read_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:14:12 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/21 17:50:18 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_pixel	**read_map(char *filename, t_map_info *map_info)
{
	t_pixel			**map;
	unsigned int	h;
	int				fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error("Error opening file.");
	map = malloc(map_info->height * sizeof(t_pixel *));
	if (!map)
		handle_error("Error allocating memory.");
	h = -1;
	while (++h < map_info->height)
		populate_line(map, map_info, fd, h);
	close(fd);
	return (map);
}

void	populate_line(t_pixel **map, t_map_info *map_info, int fd, int h)
{
	unsigned int	w;
	char			**splitted_line;

	map[h] = malloc(map_info->width * sizeof(t_pixel));
	if (!map[h])
		handle_error("Error allocating memory.");
	splitted_line = get_coordinates_from_line(fd);
	w = -1;
	while (++w < map_info->width)
	{
		populate_pixel_matrix(&map[h][w], splitted_line[w], h, w);
		refresh_min_and_max_z(map[h][w].z_axis, map_info);
	}
	ft_free_str_array(splitted_line);
}

char	**get_coordinates_from_line(int fd)
{
	char	*line;
	char	**coordinates;

	line = ft_get_next_line(fd);
	coordinates = ft_split(line, ' ');
	free(line);
	return (coordinates);
}

void	populate_pixel_matrix(t_pixel *pixel, char *str, int h, int w)
{
	pixel->x_axis = w;
	pixel->y_axis = h;
	pixel->z_axis = ft_atoi(str);
	pixel->rgba_channel = get_color(str);
}

uint32_t	get_color(char *coordinate)
{
	char		*comma_address;
	char		*hexadecimal;
	uint32_t	color;

	comma_address = ft_strchr(coordinate, ',');
	if (comma_address)
	{
		hexadecimal = ft_strtolower(comma_address + 3);
		color = (ft_atoi_base(hexadecimal, "0123456789abcdef") << 8) | 0xff;
		return (color);
	}
	return (0xffffffff);
}
