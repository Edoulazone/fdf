/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:51:57 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 19:53:25 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_zoom_keys(int key, t_fdf *fdf)
{
	if (key == KEY_PLUS || key == KEY_PLUS_ALT || key == 61)
		zoom_map(fdf, 1.1f);
	else if (key == KEY_MINUS || key == KEY_MINUS_ALT || key == 45)
		zoom_map(fdf, 1.0f / 1.1f);
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
