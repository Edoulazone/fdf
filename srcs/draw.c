/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:37:28 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 18:54:35 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	in_bounds(int x, int y)
{
	return (is_in_bounds(x, y));
}

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	int	pixel;

	if (!in_bounds(x, y))
		return ;
	pixel = y * fdf->img.line_len + x * (fdf->img.bpp / 8);
	if (fdf->img.endian == 0)
	{
		fdf->img.data[pixel] = color & 0xFF;
		fdf->img.data[pixel + 1] = (color >> 8) & 0xFF;
		fdf->img.data[pixel + 2] = (color >> 16) & 0xFF;
		fdf->img.data[pixel + 3] = (color >> 24) & 0xFF;
	}
	else
	{
		fdf->img.data[pixel] = (color >> 24) & 0xFF;
		fdf->img.data[pixel + 1] = (color >> 16) & 0xFF;
		fdf->img.data[pixel + 2] = (color >> 8) & 0xFF;
		fdf->img.data[pixel + 3] = color & 0xFF;
	}
}

void	init_line(t_line *line, t_point p1, t_point p2)
{
	line->dx = abs((int)p2.proj_x - (int)p1.proj_x);
	line->dy = abs((int)p2.proj_y - (int)p1.proj_y);
	if ((int)p1.proj_x < (int)p2.proj_x)
		line->sx = 1;
	else
		line->sx = -1;
	if ((int)p1.proj_y < (int)p2.proj_y)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
}

void	draw_step(int *x, int *y, t_line *line)
{
	int	err2;

	err2 = 2 * line->err;
	if (err2 > -line->dy)
	{
		line->err -= line->dy;
		*x += line->sx;
	}
	if (err2 < line->dx)
	{
		line->err += line->dx;
		*y += line->sy;
	}
}

void	draw_line(t_fdf *fdf, t_point p1, t_point p2, int color)
{
	t_line	line;
	int		x;
	int		y;

	x = (int)p1.proj_x;
	y = (int)p1.proj_y;
	init_line(&line, p1, p2);
	while (1)
	{
		put_pixel(fdf, x, y, color);
		if (x == (int)p2.proj_x && y == (int)p2.proj_y)
			break ;
		draw_step(&x, &y, &line);
	}
}
