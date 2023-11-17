/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_and_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:23:02 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/17 14:50:46 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//testar saida do programa com mapa invalido
//cuidar com leak da GNL
// tratar os errors com errno e tals

static unsigned int	get_width(char *line)
{
	unsigned int	width;
	int				i;
	int				new_word;

	width = 0;
	i = 0;
	new_word = 1;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && new_word == 1)
		{
			width++;
			new_word = 0;
		}
		if (line[i] == ' ')
			new_word = 1;
		i++;
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
			ft_get_next_line(-fd);
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
	fdf->map_info.max_z = INT_MIN;
	fdf->map_info.min_z = INT_MAX;
	if (fdf->map_info.height < 3 || fdf->map_info.width < 3)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
