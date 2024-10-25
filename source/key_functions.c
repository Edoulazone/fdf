/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:08:07 by eschmitz          #+#    #+#             */
/*   Updated: 2024/07/17 15:44:18 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate_left(t_point *points, t_mlx_data *data)
{
	int	i;

	i = 0;
	while (points[i].x != -1)
	{
		(points)[i].projected_x -= 30;
		i++;
	}
	mlx_destroy_image(data->mlx_connection, data->image->image_ptr);
	draw(data, points);
}

void	translate_right(t_point *points, t_mlx_data *data)
{
	int	i;

	i = 0;
	while (points[i].x != -1)
	{
		(points)[i].projected_x += 30;
		i++;
	}
	mlx_destroy_image(data->mlx_connection, data->image->image_ptr);
	draw(data, points);
}

void	translate_down(t_point *points, t_mlx_data *data)
{
	int	i;

	i = 0;
	while (points[i].x != -1)
	{
		(points)[i].projected_y -= 30;
		i++;
	}
	mlx_destroy_image(data->mlx_connection, data->image->image_ptr);
	draw(data, points);
}

void	translate_up(t_point *points, t_mlx_data *data)
{
	int	i;

	i = 0;
	while (points[i].x != -1)
	{
		(points)[i].projected_y += 30;
		i++;
	}
	mlx_destroy_image(data->mlx_connection, data->image->image_ptr);
	draw(data, points);
}

void	rotation_x(t_point *points, t_mlx_data *data)
{
	int		i;
	float	center_x;
	float	center_y;

	center_x = (WIDTH / 2.0);
	center_y = HEIGHT / 2.0;
	i = 0;
	while (points[i].x != -1)
	{
		data->translated_x = points[i].projected_x - center_x;
		data->translated_y = points[i].projected_y - center_y;
		data->rotated_x = cos(0.15708) * data->translated_x
			- sin(0.15708) * data->translated_y;
		data->rotated_y = sin(0.15708) * data->translated_x
			+ cos(0.15708) * data->translated_y;
		points[i].projected_x = data->rotated_x + center_x;
		points[i].projected_y = data->rotated_y + center_y;
		i++;
	}
	mlx_destroy_image(data->mlx_connection, data->image->image_ptr);
	draw(data, points);
}
