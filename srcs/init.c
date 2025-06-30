/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:36:14 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 18:15:09 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	calc_zoom(t_map *map)
{
	float	zoom_x;
	float	zoom_y;
	float	zoom;

	if (map->width == 0 || map->height == 0)
		return (1.0f);
	zoom_x = (WIN_WIDTH * 0.8f) / (map->width * 1.5f);
	zoom_y = (WIN_HEIGHT * 0.8f) / (map->height * 1.5f);
	if (zoom_x < zoom_y)
		zoom = zoom_x;
	zoom = zoom_y;
	if (zoom < 1.0f)
		zoom = 1.0f;
	else if (zoom > 20.0f)
		zoom = 20.0f;
	return (zoom);
}

int	init_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		exit_error("Failed to initialize MLX\n");
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (!fdf->win)
		exit_error("Failed to create window\n");
	return (0);
}

int	init_image(t_fdf *fdf)
{
	fdf->img.ptr = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img.ptr)
		exit_error("Failed to create image\n");
	fdf->img.data = mlx_get_data_addr(fdf->img.ptr, &fdf->img.bpp,
			&fdf->img.line_len, &fdf->img.endian);
	return (0);
}

void	cleanup_fdf(t_fdf *fdf)
{
	if (fdf->img.ptr)
		mlx_destroy_image(fdf->mlx, fdf->img.ptr);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->map.points)
		free(fdf->map.points);
}

int	init_fdf(t_fdf *fdf, char *filename)
{
	t_map	*map;

	ft_memset(fdf, 0, sizeof(t_fdf));
	map = parse_map(filename);
	if (!map)
		exit_error("Failed to parse map\n");
	if (map->width <= 1 || map->height <= 1)
	{
		free(map->points);
		free(map);
		exit_error("Map too small\n");
	}
	fdf->map = *map;
	free(map);
	init_mlx(fdf);
	init_image(fdf);
	fdf->zoom = calc_zoom(&fdf->map);
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	return (0);
}
