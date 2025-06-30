/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:36:39 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 19:54:31 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_dimensions2(char *line, int *width, int *height)
{
	*width = count_words(line, ' ');
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	free(line);
	*height = 1;
}

int	get_dimensions(char *filename, int *width, int *height)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	*height = 0;
	*width = 0;
	line = get_next_line(fd);
	if (line)
		get_dimensions2(line, width, height);
	line = get_next_line(fd);
	while (line)
	{
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (*width > 0 && *height > 0)
		return (0);
	return (-1);
}

void	parse_line(char *line, t_point *points, int y, int width)
{
	char	**values;
	int		x;
	int		index;

	if (!line || !points)
		return ;
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	values = split_line(line, ' ');
	if (!values)
		return ;
	x = 0;
	while (values[x] && x < width)
	{
		index = y * width + x;
		fill_point(&points[index], values[x], x, y);
		x++;
	}
	free_split(values);
}

int	parse_map2(t_map *map, char *filename)
{
	if (!map)
		return (-1);
	if (get_dimensions(filename, &map->width, &map->height) < 0)
		return (-1);
	map->total = map->width * map->height;
	map->points = malloc(sizeof(t_point) * map->total);
	if (!map->points)
		return (-1);
	return (0);
}

t_map	*parse_map(char *filename)
{
	t_map	*map;
	int		fd;
	char	*line;
	int		y;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	if (parse_map2(map, filename) < 0)
	{
		free(map);
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	y = 0;
	line = get_next_line(fd);
	while (line && y < map->height)
	{
		parse_line(line, map->points, y, map->width);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}
