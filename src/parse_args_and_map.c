/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_and_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:23:02 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/14 22:38:16 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// tratar os errors com errno e tals

static unsigned int	get_width(char *line)
{
	unsigned int	width;
	char			**splitted_line;

	width = 0;
	if (line)
	{
		splitted_line = ft_split(line, ' ');
		while (splitted_line[width])
			width++;
		if (!ft_isprint(*splitted_line[width - 1]))
		{
			ft_free_ptr_array((void **)splitted_line, width);
			--width;
		}
		else
			ft_free_ptr_array((void **)splitted_line, width);
	}
	return (width);
}

static unsigned int	get_height_and_check_width(int fd, unsigned int map_width)
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
			return (0);
		}
		width = 0;
		free(line);
		line = ft_get_next_line(fd);
	}
	free(line);
	return (height);
}

int	parse_args_and_map(int argc, char **argv, t_fdf *fdf)
{
	int		fd;
	char	*line;

	if (argc != 2)
		return (ft_printf("Correct usage: ./fdf maps/map_name.fdf"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_printf("Invalid filename"));
	line = ft_get_next_line(fd);
	fdf->map_info.width = get_width(line);
	fdf->map_info.height = get_height_and_check_width(fd, fdf->map_info.width);
	close(fd);
	free(line);
	if (fdf->map_info.height < 3 || fdf->map_info.width < 3)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
