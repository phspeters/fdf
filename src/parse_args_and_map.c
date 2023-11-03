/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_and_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@42sp.com.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:23:02 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/03 16:40:09 by pehenri2         ###   ########.fr       */
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

int	parse_args_and_map(int argc, char **argv, t_master *master)
{
	int		fd;
	char	*line;

	if (argc != 2)
		return (ft_printf("Correct usage: ./fdf maps/map_name.fdf"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_printf("Invalid filename"));
	line = ft_get_next_line(fd);
	master->map_width = get_width(line);
	master->map_height = get_height_and_check_width(fd, master->map_width);
	close(fd);
	free(line);
	if (master->map_height < 3 || master->map_width < 3)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
