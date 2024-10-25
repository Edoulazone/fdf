/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:57:33 by eschmitz          #+#    #+#             */
/*   Updated: 2024/07/17 15:10:22 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*get_points(char *file_name)
{
	int		size;
	t_point	*points;

	size = count_columns(file_name) * count_lines(file_name);
	if (size == -1)
	{
		write(2, "Error: nothing to read\n", 23);
		exit(1);
	}
	points = malloc(sizeof(t_point) * (size + 1));
	if (!points)
		exit(1);
	points[size].x = -1;
	points[size].y = -1;
	return (points);
}

void	loop_parse(t_point *points, char *line)
{
	static int	k = 0;
	char		**array;
	int			i;
	int			count;

	array = ft_split(line, ' ');
	if (!array)
		exit_malloc();
	count = count_number(array);
	i = -1;
	while (array[++i])
	{
		if (ft_strncmp(array[i], "\n", 1) == 0)
			break ;
		points[k].x = i;
		points[k].y = k / count;
		points[k].z = ft_atoi(array[i]);
		if (ft_strchr(array[i], ',') == NULL)
			points[k].colour = ft_atoi_hexa("CD28B5");
		else
			points[k].colour = ft_atoi_hexa(ft_strchr(array[i], 'x') + 1);
		k++;
	}
	free_tab(array);
}

t_point	*parsing(char **argv)
{
	t_point	*points;
	char	*line;
	int		fd;

	points = get_points(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_error();
	line = get_next_line(fd);
	while (line)
	{
		loop_parse(points, line);
		free(line);
		line = get_next_line(fd);
	}
	return (points);
}
