/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:37:49 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 17:55:17 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*gnl_read_buffer(int fd)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	return (buffer);
}

char	*gnl_join_free(char *s1, char *s2)
{
	char	*result;
	char	*temp;

	if (!s1)
		s1 = ft_strdup("");
	temp = s1;
	result = ft_strjoin(s1, s2);
	free(temp);
	free(s2);
	return (result);
}

char	*gnl_extract_line(char **save)
{
	char	*line;
	char	*newline_pos;
	char	*new_save;
	int		len;

	if (!*save)
		return (NULL);
	newline_pos = ft_strchr(*save, '\n');
	if (newline_pos)
	{
		len = newline_pos - *save + 1;
		line = ft_substr(*save, 0, len);
		new_save = ft_strdup(newline_pos + 1);
		free(*save);
		*save = new_save;
		if (*save && **save == '\0')
		{
			free(*save);
			*save = NULL;
		}
		return (line);
	}
	return (NULL);
}

char	*gnl_read_until_newline(int fd, char **save)
{
	char	*buffer;

	while (!ft_strchr(*save, '\n'))
	{
		buffer = gnl_read_buffer(fd);
		if (!buffer)
			break ;
		*save = gnl_join_free(*save, buffer);
		if (!*save)
			return (NULL);
	}
	return (*save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!gnl_read_until_newline(fd, &save))
	{
		if (save && *save)
		{
			line = ft_strdup(save);
			free(save);
			save = NULL;
			return (line);
		}
		return (NULL);
	}
	line = gnl_extract_line(&save);
	return (line);
}
