/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:37:40 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 20:02:26 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_map(t_fdf *fdf, float factor)
{
	fdf->zoom *= factor;
	if (fdf->zoom < 0.1f)
		fdf->zoom = 0.1f;
	else if (fdf->zoom > 50.0f)
		fdf->zoom = 50.0f;
	ft_printf("🔍 Zoom: %.2f (facteur: %.1f)\n", fdf->zoom, factor);
	render_map(fdf);
}

void	translate_map(t_fdf *fdf, float dx, float dy)
{
	fdf->offset_x += dx;
	fdf->offset_y += dy;
	ft_printf("📍 Position: (%.0f, %.0f)\n", fdf->offset_x, fdf->offset_y);
	render_map(fdf);
}

void	rotate_map(t_fdf *fdf)
{
	int		i;
	float	temp_x;
	float	temp_y;
	float	center_x;
	float	center_y;

	center_x = fdf->map.width / 2.0f;
	center_y = fdf->map.height / 2.0f;
	i = 0;
	while (i < fdf->map.total)
	{
		temp_x = fdf->map.points[i].x - center_x;
		temp_y = fdf->map.points[i].y - center_y;
		fdf->map.points[i].x = temp_x * 0.98769f - temp_y * 0.15643f + center_x;
		fdf->map.points[i].y = temp_x * 0.15643f + temp_y * 0.98769f + center_y;
		i++;
	}
	ft_printf("🔄 Rotation appliquee (angle: 9 degres)\n");
	render_map(fdf);
}

int	handle_close(t_fdf *fdf)
{
	cleanup_fdf(fdf);
	exit(0);
	return (0);
}
