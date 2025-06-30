/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:37:16 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 17:55:41 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_fdf *fdf)
{
	int	total_pixels;
	int	i;

	total_pixels = WIN_WIDTH * WIN_HEIGHT * (fdf->img.bpp / 8);
	i = 0;
	while (i < total_pixels)
	{
		fdf->img.data[i] = BG_COLOR & 0xFF;
		fdf->img.data[i + 1] = (BG_COLOR >> 8) & 0xFF;
		fdf->img.data[i + 2] = (BG_COLOR >> 16) & 0xFF;
		fdf->img.data[i + 3] = 0;
		i += 4;
	}
}

void	apply_projection(t_map *map, float zoom)
{
	int		i;
	float	x;
	float	y;
	float	z;

	i = 0;
	while (i < map->total)
	{
		x = map->points[i].x * zoom;
		y = map->points[i].y * zoom;
		z = map->points[i].z * zoom * 0.5f;
		map->points[i].proj_x = (x - y) * 0.866025f;
		map->points[i].proj_y = (x + y) * 0.5f - z;
		i++;
	}
}

void	center_map(t_map *map, float ox, float oy)
{
	int		i;
	float	center_x;
	float	center_y;

	center_x = WIN_WIDTH * 0.5f + ox;
	center_y = WIN_HEIGHT * 0.5f + oy;
	i = 0;
	while (i < map->total)
	{
		map->points[i].proj_x += center_x;
		map->points[i].proj_y += center_y;
		i++;
	}
}

void	draw_connections(t_fdf *fdf)
{
	int		i;
	int		x;
	int		y;
	t_point	*pts;

	pts = fdf->map.points;
	i = 0;
	while (i < fdf->map.total)
	{
		x = i % fdf->map.width;
		y = i / fdf->map.width;
		put_pixel(fdf, (int)pts[i].proj_x, (int)pts[i].proj_y, pts[i].color);
		if (x < fdf->map.width - 1)
			draw_line(fdf, pts[i], pts[i + 1], pts[i].color);
		if (y < fdf->map.height - 1)
			draw_line(fdf, pts[i], pts[i + fdf->map.width], pts[i].color);
		i++;
	}
}

void	render_map(t_fdf *fdf)
{
	clear_image(fdf);
	apply_projection(&fdf->map, fdf->zoom);
	center_map(&fdf->map, fdf->offset_x, fdf->offset_y);
	draw_connections(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.ptr, 0, 0);
}
