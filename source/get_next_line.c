/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:03:18 by eschmitz          #+#    #+#             */
/*   Updated: 2024/07/15 14:47:10 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free_return(char **str, int must_free)
{
	if (must_free)
		free(*str);
	*str = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;
	char		*buffer;

	if (BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (ft_free_return(&save, 1));
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free_return(&save, 1));
	line = read_line(fd, save, buffer);
	free(buffer);
	if (!line)
		return (ft_free_return(&save, 0));
	save = ft_save(&line);
	return (line);
}

char	*read_line(int fd, char *save, char *buffer)
{
	int		read_bytes;
	char	*temp;

	while (!ft_strchr(save, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (ft_free_return(&save, 1));
		else if (read_bytes == 0)
			break ;
		buffer[read_bytes] = 0;
		if (!save)
			save = ft_strdup("");
		temp = save;
		save = ft_strjoin(temp, buffer);
		free(temp);
	}
	return (save);
}

char	*ft_save(char **line_buff)
{
	int		i;
	char	*carry;
	char	*tmp;

	i = 0;
	tmp = *line_buff;
	while (tmp[i] != '\0' && tmp[i] != '\n')
		i++;
	if (tmp[i] == 0 || tmp[1] == 0)
		return (NULL);
	carry = ft_substr(*line_buff, i + 1, ft_strlen(tmp) - i);
	if (!carry)
		return (NULL);
	if (*carry == 0)
		ft_free_return(&carry, 1);
	tmp[i + 1] = 0;
	*line_buff = ft_substr(tmp, 0, i + 1);
	free(tmp);
	if (!*line_buff)
		return (ft_free_return(&carry, 1));
	return (carry);
}
