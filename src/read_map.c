/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:14:12 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/14 22:31:53 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	**get_coordinates_from_line(int fd)
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

void	set_min_and_max_z(int z_axis, t_map_info *map_info)
{
	if (z_axis > map_info->max_z)
		map_info->max_z = z_axis;
	if (z_axis < map_info->min_z)
		map_info->min_z = z_axis;
}

//checar se não está tendo leak após mudanças
t_pixel	**read_map(char *filename, t_map_info *map_info)
{
	t_pixel			**map;
	unsigned int	h;
	unsigned int	w;
	int				fd;
	char			**splitted_line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(map_info->height * sizeof(t_pixel *));
	h = -1;
	while (++h < map_info->height)
	{
		map[h] = malloc(map_info->width * sizeof(t_pixel));
		splitted_line = get_coordinates_from_line(fd);
		w = -1;
		while (++w < map_info->width)
		{
			populate_pixel_matrix(&map[h][w], splitted_line[w], h, w);
			set_min_and_max_z(map[h][w].z_axis, map_info);
		}
		ft_free_str_array(splitted_line);
	}
	close(fd);
	return (map);
}
