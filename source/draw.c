/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:11:41 by eschmitz          #+#    #+#             */
/*   Updated: 2024/08/05 15:15:07 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_line(t_mlx_data *data, float *x, float *y)
{
	*x = (int)*x;
	*y = (int)*y;
	if (data->error2 > -data->dy)
	{
		data->error -= data->dy;
		*x += data->sx;
	}
	if (data->error2 < data->dx)
	{
		data->error += data->dx;
		*y += data->sy;
	}
}

void	draw_point(t_mlx_data *data, int x, int y, int colour)
{
	int	pixel;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel = y * data->image->size_line + x * data->image->bits_per_pixel
			/ 8;
		if (data->image->endian == 0)
		{
			data->image->image_pixels_ptr[pixel + 0] = (colour & 0xFF);
			data->image->image_pixels_ptr[pixel + 1] = (colour >> 8) & 0xFF;
			data->image->image_pixels_ptr[pixel + 2] = (colour >> 16) & 0xFF;
			data->image->image_pixels_ptr[pixel + 3] = (colour >> 24) & 0xFF;
		}
		else
		{
			data->image->image_pixels_ptr[pixel + 0] = (colour >> 24) & 0xFF;
			data->image->image_pixels_ptr[pixel + 1] = (colour >> 16) & 0xFF;
			data->image->image_pixels_ptr[pixel + 2] = (colour >> 8) & 0xFF;
			data->image->image_pixels_ptr[pixel + 3] = (colour & 0xFF);
		}
	}
}

void	draw_line(t_mlx_data *data, t_point start, t_point end, int colour)
{
	start.projected_x = (int)start.projected_x;
	start.projected_y = (int)start.projected_y;
	end.projected_x = (int)end.projected_x;
	end.projected_y = (int)end.projected_y;
	data->dx = fabsf(end.projected_x - start.projected_x);
	data->dy = fabsf(end.projected_y - start.projected_y);
	data->sx = -1;
	data->sy = -1;
	if (start.projected_x < end.projected_x)
		data->sx = 1;
	if (start.projected_y < end.projected_y)
		data->sy = 1;
	data->error = data->dx - data->dy;
	while (!(start.projected_x == end.projected_x && start.projected_y
			== end.projected_y))
	{
		draw_point(data, start.projected_x, start.projected_y, colour);
		data->error2 = 2 * data->error;
		check_line(data, &start.projected_x, &start.projected_y);
	}
}

void	loop_draw(t_mlx_data *data)
{
	int	i;
	int	j;
	int	pixel;

	i = -1;
	while (++i < 1400)
	{
		j = -1;
		while (++j < 2560)
		{
			pixel = i * data->image->size_line + j * 4;
			data->image->image_pixels_ptr[pixel + 0] = 0x16;
			data->image->image_pixels_ptr[pixel + 1] = 0x16;
			data->image->image_pixels_ptr[pixel + 2] = 0x15;
			data->image->image_pixels_ptr[pixel + 3] = 0x00;
		}
	}
}

void	draw(t_mlx_data *data, t_point *points)
{
	int	i;

	data->image->image_ptr = mlx_new_image(data->mlx_connection, 2560, 1400);
	data->image->image_pixels_ptr = mlx_get_data_addr(data->image->image_ptr,
			&(data->image->bits_per_pixel), &(data->image->size_line),
			&(data->image->endian));
	loop_draw(data);
	i = 0;
	while (i + 1 <= data->height * data->width)
	{
		draw_point(data, points[i].projected_x, points[i].projected_y,
			points[i].colour);
		if ((i + 1) % data->width > 0)
			draw_line(data, points[i], points[i + 1], points[i].colour);
		if ((i / data->width) < data->height - 1)
			draw_line(data, points[i], points[i + data->width],
				points[i].colour);
		i++;
	}
	mlx_put_image_to_window(data->mlx_connection, data->mlx_window,
		data->image->image_ptr, 0, 0);
}
