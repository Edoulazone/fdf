/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:37:40 by eschmitz          #+#    #+#             */
/*   Updated: 2025/06/30 17:53:39 by eschmitz         ###   ########.fr       */
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
	printf("🔍 Zoom: %.2f (facteur: %.1f)\n", fdf->zoom, factor);
	render_map(fdf);
}

void	translate_map(t_fdf *fdf, float dx, float dy)
{
	fdf->offset_x += dx;
	fdf->offset_y += dy;
	printf("📍 Position: (%.0f, %.0f)\n", fdf->offset_x, fdf->offset_y);
	render_map(fdf);
}

void	rotate_map(t_fdf *fdf)
{
	int		i;
	float	cos_a;
	float	sin_a;
	float	temp_x;
	float	temp_y;
	float	center_x;
	float	center_y;

	cos_a = cosf(0.15708f);
	sin_a = sinf(0.15708f);
	center_x = fdf->map.width / 2.0f;
	center_y = fdf->map.height / 2.0f;
	i = 0;
	while (i < fdf->map.total)
	{
		temp_x = fdf->map.points[i].x - center_x;
		temp_y = fdf->map.points[i].y - center_y;
		fdf->map.points[i].x = temp_x * cos_a - temp_y * sin_a + center_x;
		fdf->map.points[i].y = temp_x * sin_a + temp_y * cos_a + center_y;
		i++;
	}
	printf("🔄 Rotation appliquee (angle: 9 degres)\n");
	render_map(fdf);
}

int	handle_close(t_fdf *fdf)
{
	cleanup_fdf(fdf);
	exit(0);
	return (0);
}
