/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_and_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:23:02 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/07 15:00:01 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Parses the arguments passed to the program and checks if the map is
 * valid. It opens the file and reads the first line to get the width of the map.
 * Then it reads the rest of the file to get the height and check if all lines
 * have the same width. It also checks if the map is at least 2x2 and updates
 * the max an min Z values of the map.
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The arguments passed to the program as strings.
 * @param fdf The fdf struct that contains all the necessary information to draw
 * the map.
 * @return 0 if the arguments and map are valid. Exits the program with an error
 * message otherwise.
 */
int	parse_args_and_map(int argc, char **argv, t_fdf *fdf)
{
	int		fd;
	char	*line;

	parse_args(argc, argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		handle_error("Error opening file");
	line = ft_get_next_line(fd);
	fdf->map_info.width = get_width(line);
	free(line);
	if (fdf->map_info.width == 0)
		handle_error("The map is empty");
	fdf->map_info.height = get_height_and_check_width(fd, fdf->map_info.width);
	close(fd);
	fdf->map_info.max_z = INT_MIN;
	fdf->map_info.min_z = INT_MAX;
	if (fdf->map_info.height < 2 || fdf->map_info.width < 2)
		handle_error("Map must be at least 2x2");
	return (0);
}

/**
 * @brief Parses the arguments passed to the program. It checks if the number
 * of arguments is correct and if the map has the correct extension.
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The arguments passed to the program as strings.
 * @return 0 if the arguments are valid. Exit the program with an error message
 * otherwise.
 */
int	parse_args(int argc, char *argv)
{
	char	*file_extension;

	if (argc == 1)
		handle_error("Map name missing. Correct usage: './fdf map_name'");
	if (argc > 2)
		handle_error("Too many arguments. Correct usage: './fdf map_name'");
	file_extension = (ft_strchr(argv, '\0') - 4);
	if (ft_strncmp(".fdf", file_extension, 4) != 0)
		handle_error("Invalid extension. Map must have '.fdf' extension");
	return (0);
}

/**
 * @brief Reads the first line of the file to get the width of the map.
 * That is, the number of numbers in the first line.
 * 
 * @param line The first line of the file.
 * @return The width of the map.
 */
unsigned int	get_width(char *line)
{
	unsigned int	width;
	int				i;
	int				is_new_word;

	width = 0;
	i = 0;
	is_new_word = 1;
	if (line != NULL)
	{
		while (line[i] != '\0' && line[i] != '\n')
		{
			if (line[i] != ' ' && is_new_word == 1)
			{
				width++;
				is_new_word = 0;
			}
			if (line[i] == ' ')
				is_new_word = 1;
			i++;
		}
	}
	return (width);
}

/**
 * @brief Reads the rest of the file to get the height and check if all lines
 * have the same width as the first.
 * 
 * @param fd The file descriptor of the map file.
 * @param map_width The width of the map.
 * @return The height of the map.
 */
unsigned int	get_height_and_check_width(int fd, unsigned int map_width)
{
	char			*line;
	unsigned int	height;
	unsigned int	width;

	width = 0;
	height = 1;
	line = ft_get_next_line(fd);
	while (line)
	{
		height++;
		width = get_width(line);
		if (width != map_width)
		{
			free(line);
			ft_get_next_line(-fd);
			handle_error("Invalid map. All lines must have the same width");
		}
		free(line);
		line = ft_get_next_line(fd);
	}
	free(line);
	return (height);
}
