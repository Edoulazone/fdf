/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:36:39 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 17:53:10 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_words(char *str, char delimiter)
{
	int	count;
	int	in_word;

	if (!str)
		return (0);
	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != delimiter && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*str == delimiter)
			in_word = 0;
		str++;
	}
	return (count);
}

int	atoi_hex(char *str)
{
	int		result;
	int		i;
	char	c;

	if (!str)
		return (DEFAULT_COLOR);
	result = 0;
	i = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	while (str[i])
	{
		c = str[i];
		result *= 16;
		if (c >= '0' && c <= '9')
			result += c - '0';
		else if (c >= 'a' && c <= 'f')
			result += c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			result += c - 'A' + 10;
		else
			break ;
		i++;
	}
	return (result);
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
	{
		*width = count_words(line, ' ');
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		free(line);
		*height = 1;
	}
	while ((line = get_next_line(fd)))
	{
		(*height)++;
		free(line);
	}
	close(fd);
	return ((*width > 0 && *height > 0) ? 0 : -1);
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

t_map	*parse_map(char *filename)
{
	t_map	*map;
	int		fd;
	char	*line;
	int		y;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	if (get_dimensions(filename, &map->width, &map->height) < 0)
	{
		free(map);
		return (NULL);
	}
	map->total = map->width * map->height;
	map->points = malloc(sizeof(t_point) * map->total);
	if (!map->points)
	{
		free(map);
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	y = 0;
	while ((line = get_next_line(fd)) && y < map->height)
	{
		parse_line(line, map->points, y, map->width);
		free(line);
		y++;
	}
	close(fd);
	return (map);
}
