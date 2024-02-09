/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:14:12 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/09 10:41:42 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/**
 * @brief Opens the map file and reads from it, line by line, while populating
 * the pixel matrix with the coordinates and color of each pixel.
 * 
 * @param filename Map file name.
 * @param map_info Information about the map.
 * @return Pixel matrix with the map information.
 */
t_pixel	**read_map(char *filename, t_map_info *map_info)
{
	t_pixel			**map;
	unsigned int	h;
	int				fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error("Error opening file");
	map = malloc(map_info->height * sizeof(t_pixel *));
	if (!map)
		handle_error("Error allocating memory");
	h = -1;
	while (++h < map_info->height)
		populate_line(map, map_info, fd, h);
	close(fd);
	return (map);
}

/**
 * @brief Reads a line from the map and populates the corresponding pixels
 * with their the coordinates and color.
 * 
 * @param map The pixel matrix with the coordinates and color of each pixel.
 * @param map_info The struct that contains the information about the map.
 * @param fd The file descriptor of the file that contains the map.
 * @param h The current line of the map.
 */
void	populate_line(t_pixel **map, t_map_info *map_info, int fd, int h)
{
	unsigned int	w;
	char			**splitted_line;

	map[h] = malloc(map_info->width * sizeof(t_pixel));
	if (!map[h])
		handle_error("Error allocating memory");
	splitted_line = get_coordinates_from_line(fd);
	w = -1;
	while (++w < map_info->width)
	{
		populate_pixel_matrix(&map[h][w], splitted_line[w], h, w);
		refresh_min_and_max_z(map[h][w].z_axis, map_info);
	}
	ft_free_str_array(splitted_line);
}

/**
 * @brief Reads a line from the map and splits it into words.
 * That is strings separated by spaces.
 * 
 * @param fd The file descriptor of the file that contains the map.
 * @return The coordinates from a line of the map as an array of strings.
 */
char	**get_coordinates_from_line(int fd)
{
	char	*line;
	char	**coordinates;

	line = ft_get_next_line(fd);
	coordinates = ft_split(line, ' ');
	free(line);
	return (coordinates);
}

/**
 * @brief Populates the pixel matrix with the coordinates and color of each
 * pixel.
 * 
 * @param pixel The pixel that will be populated.
 * @param str The string that contains the coordinates and color of the pixel
 * separated by a comma.
 * @param h The current line of the map.
 * @param w The current column of the map.
 */
void	populate_pixel_matrix(t_pixel *pixel, char *str, int h, int w)
{
	pixel->x_axis = w;
	pixel->y_axis = h;
	pixel->z_axis = ft_atoi(str);
	pixel->rgba_channel = get_color(str);
}

/**
 * @brief Gets the color of a pixel from the string that contains it's 
 * z axis value and it's color. e.g. 21,0xffff, where 21 is the z-axis value
 * and 0xffff is the color (R: ff, G: ff, B: 00, A: 00). First it finds the
 * comma in the string, then it converts the hexadecimal color to an unsigned
 * integer. The maps provided do not have alpha channel, if that's the case,
 * the function sets it to 0xff because the channel is required by the MLX42
 * library.
 * 
 * @param coordinate The string that contains the coordinates and color of the
 * pixel.
 * @return The color of the pixel.
 */
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
