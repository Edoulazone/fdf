/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:32:10 by eschmitz          #+#    #+#             */
/*   Updated: 2024/08/05 15:21:02 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	number_words(char const *s, char c)
{
	size_t	words;
	size_t	indice;

	words = 0;
	while (*s)
	{
		indice = 0;
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
		{
			if (indice == 0)
			{
				words++;
				indice = 1;
			}
			s++;
		}
	}
	return (words);
}

int	count_columns(char *file_name)
{
	int		count;
	char	*line;
	int		fd;

	fd = open(file_name, O_RDONLY, 0777);
	if (fd == -1)
		exit_error();
	count = 0;
	line = get_next_line(fd);
	if (!line)
		return (-1);
	count = number_words(line, ' ');
	if (*(ft_strrchr(line, ' ') + 1) == '\n')
		count--;
	free(line);
	close(fd);
	return (count);
}

int	count_lines(char *file_name)
{
	int		count;
	char	*line;
	int		fd;

	count = 0;
	fd = open(file_name, O_RDONLY, 0777);
	if (fd == -1)
		exit_error();
	line = get_next_line(fd);
	while (line)
	{
		if (line)
			free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	printf("%d \n", count);
	return (count);
}

int	count_number(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		if (ft_strncmp(array[i], "\n", 1) == 0)
			break ;
	}
	return (i);
}
