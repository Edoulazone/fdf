/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:00:57 by eschmitz          #+#    #+#             */
/*   Updated: 2024/07/17 16:14:18 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	escape_handle(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx_connection, data->image->image_ptr);
	mlx_destroy_window(data->mlx_connection, data->mlx_window);
	free(data->point);
	free(data->mlx_connection);
	free(data->image);
	free(data);
	write(1, "The window got closed\n", 22);
	exit(1);
}

void	zoom_in(t_point *points, t_mlx_data *data)
{
	int	i;

	i = 0;
	while ((points)[i].x != -1)
	{
		(points)[i].projected_x *= 1.1;
		(points)[i].projected_y *= 1.1;
		(points)[i].projected_x -= 130;
		(points)[i].projected_y -= 60;
		i++;
	}
	mlx_destroy_image(data->mlx_connection, data->image->image_ptr);
	draw(data, points);
}

void	zoom_out(t_point *points, t_mlx_data *data)
{
	int	i;

	i = 0;
	while ((points)[i].x != -1)
	{
		(points)[i].projected_x *= 0.9;
		(points)[i].projected_y *= 0.9;
		(points)[i].projected_x += 130;
		(points)[i].projected_y += 60;
		i++;
	}
	mlx_destroy_image(data->mlx_connection, data->image->image_ptr);
	draw(data, points);
}

int	key_handle(int key, t_mlx_data *data)
{
	if (key == KEY_ESC)
		escape_handle(data);
	else if (key == KEY_PLUS_PAD)
		zoom_in(data->point, data);
	else if (key == KEY_MINUS_PAD)
		zoom_out(data->point, data);
	else if (key == KEY_LEFT)
		translate_left(data->point, data);
	else if (key == KEY_RIGHT)
		translate_right(data->point, data);
	else if (key == KEY_DOWN)
		translate_down(data->point, data);
	else if (key == KEY_UP)
		translate_up(data->point, data);
	else if (key == KEY_X)
		rotation_x(data->point, data);
	return (0);
}
