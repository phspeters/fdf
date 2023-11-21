/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parse_args_and_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:23:02 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/20 21:03:51 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	parse_args_and_map(int argc, char **argv, t_fdf *fdf)
{
	int		fd;
	char	*line;

	if (parse_args(argc, argv[1]))
		return (EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error opening file"));
	line = ft_get_next_line(fd);
	fdf->map_info.width = get_width(line);
	if (fdf->map_info.width == 0)
		return (ft_printf("Map is empty"));
	free(line);
	fdf->map_info.height = get_height_and_check_width(fd, fdf->map_info.width);
	close(fd);
	fdf->map_info.max_z = INT_MIN;
	fdf->map_info.min_z = INT_MAX;
	if (fdf->map_info.height < 3 || fdf->map_info.width < 3)
		return (ft_printf("Map must be at least 2x2"));
	return (EXIT_SUCCESS);
}

int	parse_args(int argc, char *argv)
{
	char	*file_extension;

	if (argc == 1)
		return (ft_printf("Map name missiong. Correct usage: './fdf map_name'"));
	if (argc > 2)
		return (ft_printf("Too many arguments. Correct usage: './fdf_bonus map_name'"));
	file_extension = (ft_strchr(argv, '\0') - 4);
	if (ft_strncmp(".fdf", file_extension, 4) != 0)
		return (ft_printf("Invalid extension. Map must have '.fdf' extension"));
	return (EXIT_SUCCESS);
}

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
			return (0);
		}
		free(line);
		line = ft_get_next_line(fd);
	}
	free(line);
	return (height);
}
