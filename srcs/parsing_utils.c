/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:36:52 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 17:57:34 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hex_to_int(char c)
{
	return (hex_char_to_int(c));
}

int	extract_color(char *str)
{
	char	*color_str;

	color_str = ft_strchr(str, ',');
	if (color_str && *(color_str + 1) == '0' && *(color_str + 2) == 'x')
		return (atoi_hex(color_str + 3));
	return (DEFAULT_COLOR);
}

void	fill_point(t_point *point, char *value, int x, int y)
{
	point->x = (float)x;
	point->y = (float)y;
	point->z = (float)ft_atoi(value);
	point->color = extract_color(value);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**allocate_split_array(int word_count)
{
	char	**result;

	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	return (result);
}
